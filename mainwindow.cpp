#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addpassword.h"
#include "ui_addpassword.h"

#include "QMessageBox"
#include <QTimer>
#include <QFileDialog>
#include <QString>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui -> setupUi(this);

    QString projectDir = QCoreApplication::applicationDirPath();
    QString folderPath = projectDir;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(receivedText);

    if (!db.open()) {
        QMessageBox::critical(this, "Błąd", "Nie udało się połączyć z bazą danych.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::readDirectly(addPassword *dialog) {
    QString text = dialog -> ui -> textEdit -> toPlainText();
    return text;
}

void MainWindow::addData(){
    addPassword *dialog = new addPassword(this);
    if (dialog->exec() == QDialog::Accepted) {
    QString entry = readDirectly(dialog);
    ui -> listWidget -> addItem(entry);
    }
    dialog -> deleteLater();
}

void MainWindow::loadDatabase(){

}

void MainWindow::on_pushButton_2_clicked()
{
    addData();
}

void MainWindow::receiveText(const QString &text)
{
    QString receivedText = text + ".db";
}

void MainWindow::on_pushButton_clicked()
{

}

