#include "database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDebug>


bool Database::createNewDatabase(const QString &path) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qWarning() << "Failed to create or open the database:" << db.lastError().text();
        db.close();
        return false;
    }

    QString sql = "CREATE TABLE IF NOT EXISTS passwords ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "hashedPassword TEXT NOT NULL, "
                  "login TEXT NOT NULL)";

    QSqlQuery query;
    if (!query.exec(sql)) {
        qWarning() << "Create table failed:" << query.lastError().text();
        db.close();
        return false;
    }

    db.close();
    return true;
}

bool Database::insertLoginData(const QString &path, const QString &login, const QString &password) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qWarning() << "Failed to open database:" << db.lastError().text();
        db.close();
        return false;
    }

    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPassword = hash.toHex();

    QString sql = QString("INSERT INTO passwords (hashedPassword, login) "
                          "VALUES (:hashedPassword, :login)");

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":hashedPassword", hashedPassword);
    query.bindValue(":login", login);

    if (!query.exec()) {
        qWarning() << "Insert failed:" << query.lastError().text();
        db.close();
        return false;
    }

    db.close();
    return true;
}
