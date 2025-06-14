#include "mypopup.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyPopup popup;
    popup.show();

    return a.exec();
}
