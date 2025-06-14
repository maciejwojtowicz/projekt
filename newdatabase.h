#ifndef NEWDATABASE_H
#define NEWDATABASE_H

#include <QDialog>

namespace Ui {
class newdatabase;
}

class newdatabase : public QDialog
{
    Q_OBJECT

public:
    explicit newdatabase(QDialog *parent = nullptr);
    ~newdatabase();

private:
    Ui::newdatabase *ui;
};

#endif // NEWDATABASE_H
