#include "newdatabase.h"
#include "mainwindow.h"
#include "ui_newdatabase.h"
#include "database.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

newdatabase::newdatabase(QDialog *parent)
    : QDialog(parent), ui(new Ui::newdatabase) {
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {
        QString filename = QFileDialog::getSaveFileName(this, "Utwórz bazę danych", "", "SQLite DB (*.db)");


        QString loginText = ui -> linePopup -> text();

        if (!filename.isEmpty()) {
            ui->linePopup->setText(filename);
        }

        QString login = ui -> linePopup -> text();
        QString password = ui -> linePopup_2 -> text();
        QString reppassword = ui -> linePopup_3 -> text();
        QString projectDir = QCoreApplication::applicationDirPath();
        QDir dir(projectDir);
        QString path = dir.filePath(login);


        if (path.isEmpty()) {
            QMessageBox::warning(this, "Błąd", "Podaj nazwę pliku.");
            return;
        }

        if (Database::createNewDatabase(path) && (password == reppassword)) {
            if (Database::insertLoginData(path, loginText, password)){
            QMessageBox::information(this, "Sukces", "Utworzono bazę danych.");
            MainWindow *w = new MainWindow;
            w->show();
            close();
            }
        }

        else {
            QMessageBox::critical(this, "Błąd", "Nie udało się utworzyć bazy.");
        }
    });
}

newdatabase::~newdatabase() {
    delete ui;
}
