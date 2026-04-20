#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DataBase
{
private:
    static DataBase* p_instance;
    QSqlDatabase db;

    DataBase() {}
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;

    ~DataBase() {
        if (db.isOpen())
            db.close();
    }

public:
    static DataBase* getInstance();

    bool init(const QString& dbPath = "timp.db");

    bool    registerUser(const QString& login, const QString& password);
    bool    authUser(const QString& login, const QString& password);
    bool    loginExists(const QString& login);

    bool    updateSocketID(const QString& login, const QString& socketID);
    QString getLoginBySocket(const QString& socketID);
    bool    logoutUser(const QString& login);

    QString getStatsByLogin(const QString& login);
};

#endif // DATABASE_H
