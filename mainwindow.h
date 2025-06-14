#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addpassword.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:

    QString readDirectly(addPassword *dialog);
    QString receivedText;
    void addData();
    void loadDatabase();
    void receiveText(const QString &text);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
