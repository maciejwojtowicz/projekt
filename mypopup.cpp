#include "mypopup.h"
#include "ui_mypopup.h"
#include "newdatabase.h"
#include "mainwindow.h"

#include "QDir"
#include "QFileInfoList"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"
#include "QCryptographicHash"
#include <QDebug>  // Dodajemy QDebug dla logowania

#include <QTimer>
#include <QCoreApplication>
#include <QString>
#include "QMessageBox"


MyPopup::MyPopup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyPopup)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog);

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        QString login = ui->linePopup->text();
        QString password = ui->linePopup_2->text();
        QString readLogin;
        QString readPassword;
        QString projectDir = QCoreApplication::applicationDirPath();
        qDebug() << projectDir;
        QString folderPath = projectDir;

        if (!login.isEmpty()) {
            QString dbFileName = findDatabase(folderPath, login, password, readLogin, readPassword);

            if (!dbFileName.isEmpty()) {
                QMessageBox::information(this, "Sukces", "Zalogowano pomyślnie!");
                MainWindow *w = new MainWindow;
                this->close();
                w->show();
            } else {
                QMessageBox::warning(this, "Błąd!", "Nie znaleziono odpowiedniej bazy danych!");
            }
        } else {
            QMessageBox::information(this, "Błąd!", "Wprowadź odpowiednie dane!");
        }
    });
}

MyPopup::~MyPopup()
{
    delete ui;
}

QString MyPopup::findDatabase(const QString &folderPath, const QString &login, const QString &password, QString &readLogin, QString &readPassword)
{
    QDir dir(folderPath);
    QStringList filters;
    filters << "*.db";  // Filtrujemy tylko pliki z rozszerzeniem .db
    dir.setNameFilters(filters);

    QFileInfoList fileList = dir.entryInfoList();

    for (const QFileInfo &fileInfo : std::as_const(fileList)) {
        QString dbPath = fileInfo.absoluteFilePath();

        // Logowanie ścieżki do bazy danych
        qDebug() << "Sprawdzanie bazy danych: " << dbPath;

        if (checkDatabase(dbPath, login, password, readLogin, readPassword) == true) {
            qDebug() << "znaleziono";
            return dbPath;
        }
    }
    return "";
}

bool MyPopup::checkDatabase(const QString &dbPath, const QString &login, const QString &password, QString &readLogin, QString &readPassword)
{
    // Używamy jednej instancji bazy danych, aby uniknąć wielokrotnego tworzenia połączeń
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);  // Ustawiamy pełną ścieżkę do bazy danych

    // Sprawdzamy, czy połączenie z bazą jest możliwe
    if (!db.open()) {
        qWarning() << "Nie udało się otworzyć bazy danych:" << db.lastError().text();
        return false;
    }

    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPassword = hash.toHex();
    QSqlQuery query;


        query.prepare("SELECT * FROM passwords");
        qDebug() << "Wykonywanie zapytania: " << query.lastQuery();
        query.bindValue(":hashedPassword", hashedPassword);
        qDebug()<<"haslo" << hashedPassword;
        query.bindValue(":login", login);
        qDebug()<<"login" << login;



        if (!query.exec()) {
            qWarning() << "Błąd zapytania:" << query.lastError().text();
            return false;
        }

        while (query.next()) {

            readPassword = query.value("hashedPassword").toString();
            qDebug()<<"odczytane login" << readPassword;
            readLogin = query.value("login").toString();
            qDebug()<<"odczytane haslo" << readLogin;

            // Jeśli hasło i login pasują, zwracamy true
            if ((login == readLogin) && (hashedPassword == readPassword)){
                return true;
            }

        }



    return false;
}

void MyPopup::on_pushButton_2_clicked()
{
    this -> close();
    newdatabase *w = new newdatabase;
    w -> show();
}
