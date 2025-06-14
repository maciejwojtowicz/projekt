#ifndef ADDPASSWORD_H
#define ADDPASSWORD_H

#include <QDialog>

namespace Ui {
class addPassword;
}

class addPassword : public QDialog
{
    Q_OBJECT
    friend class MainWindow;

public:
    explicit addPassword(QWidget *parent = nullptr);
    ~addPassword();

    QString findDatabase(const QString &folderPath, const QString &login, const QString &password);
    bool checkDatabase(const QString &dbPath, const QString &login, const QString &password);
private:
    Ui::addPassword *ui;
};

#endif // ADDPASSWORD_H
