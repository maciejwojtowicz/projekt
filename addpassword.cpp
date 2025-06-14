#include "addpassword.h"
#include "ui_addpassword.h"


#include "QDir"
#include "QFileInfoList"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"

#include "QCryptographicHash"
#include "QMessageBox"
#include <QTimer>

addPassword::addPassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addPassword)
{
    ui->setupUi(this);

    connect(ui -> pushButton, &QPushButton::clicked, this, [=]() {
        QString text = ui -> textEdit-> toPlainText();
        QString password = ui -> textEdit_2 -> toPlainText();
        QString repPassword = ui -> textEdit_3 -> toPlainText();

        QString projectDir = QCoreApplication::applicationDirPath();
        QString folderPath = QDir(projectDir).filePath("databases");

        if (password == repPassword){
            if (!text.isEmpty()) {
                QString dbPath = findDatabase(folderPath, text, password);
                accept();
            }
            else QMessageBox::information(this,"Błąd!","Nie znaleziono bazy danych!");
        }
        else QMessageBox::information(this,"Błąd!","Nieprawidłowe powtórzenie hasła");

    });
}

addPassword::~addPassword()
{
    delete ui;
}

QString addPassword::findDatabase(const QString &folderPath, const QString &login, const QString &password){
    QDir dir(folderPath);
    QStringList filters;
    filters << "*db";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();

    for(const QFileInfo &fileInfo : std::as_const(fileList)){
        QString dbPath = fileInfo.absoluteFilePath();

        if (checkDatabase(dbPath, login, password)){
            return dbPath;
        }
    }
    return "";
}


bool addPassword::checkDatabase(const QString &dbPath, const QString &login, const QString &password){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Nie udało się otworzyć bazy danych:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM passwords WHERE login = :login AND user_password = :password");
    query.bindValue(":login", login);

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    query.bindValue(":password", hashedPassword.toHex());

    if (!query.exec()) {
        qWarning() << "Błąd zapytania:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return true;
    }

    return false;
}
