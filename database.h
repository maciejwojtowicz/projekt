#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDebug>
#include <QString>

class Database {
public:
    Database(const QString &path);
    ~Database();

    bool isOpen() const;
    bool createTable();
    bool addPassword(const QString &label, const QString &password);
    static bool insertLoginData(const QString &path, const QString &login, const QString &password);
    static bool createNewDatabase(const QString &path);
private:
    QSqlDatabase *db;
};

#endif // DATABASE_H
