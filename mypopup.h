#ifndef MYPOPUP_H
#define MYPOPUP_H

#include <QWidget>

namespace Ui {
class MyPopup;
}

class MyPopup : public QWidget
{
    Q_OBJECT

public:
    explicit MyPopup(QWidget *parent = nullptr);
    ~MyPopup();

    QString findDatabase(const QString &folderPath, const QString &login, const QString &password, QString &readLogin, QString &readPassword);
    bool checkDatabase(const QString &dbPath, const QString &login, const QString &password, QString &readLogin, QString &readPassword);

signals:
    void sendText(const QString &text);


private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MyPopup *ui;
};

#endif // MYPOPUP_H
