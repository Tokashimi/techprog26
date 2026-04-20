#include "database.h"

DataBase* DataBase::p_instance = nullptr;

DataBase* DataBase::getInstance()
{
    if (!p_instance)
        p_instance = new DataBase();
    return p_instance;
}

bool DataBase::init(const QString& dbPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Ошибка открытия БД:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS Person ("
        "  login    VARCHAR(40)  NOT NULL PRIMARY KEY,"
        "  password VARCHAR(128) NOT NULL,"
        "  socketID VARCHAR(40),"
        "  task1    INTEGER NOT NULL DEFAULT 0,"
        "  task2    INTEGER NOT NULL DEFAULT 0,"
        "  task3    INTEGER NOT NULL DEFAULT 0,"
        "  task4    INTEGER NOT NULL DEFAULT 0"
        ")"
        );

    if (!ok) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
        return false;
    }

    query.exec("UPDATE Person SET socketID = NULL WHERE socketID IS NOT NULL");
    qDebug() << "БД инициализирована:" << dbPath;
    return true;
}

bool DataBase::registerUser(const QString& login, const QString& password)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Person (login, password) VALUES (:login, :password)");
    query.bindValue(":login",    login);
    query.bindValue(":password", password);
    return query.exec();
}

bool DataBase::authUser(const QString& login, const QString& password)
{
    QSqlQuery query(db);
    query.prepare("SELECT login FROM Person WHERE login = :login AND password = :password");
    query.bindValue(":login",    login);
    query.bindValue(":password", password);
    query.exec();
    return query.next();
}

bool DataBase::loginExists(const QString& login)
{
    QSqlQuery query(db);
    query.prepare("SELECT login FROM Person WHERE login = :login");
    query.bindValue(":login", login);
    query.exec();
    return query.next();
}

bool DataBase::updateSocketID(const QString& login, const QString& socketID)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Person SET socketID = :sid WHERE login = :login");
    query.bindValue(":sid",   socketID);
    query.bindValue(":login", login);
    return query.exec();
}

QString DataBase::getLoginBySocket(const QString& socketID)
{
    QSqlQuery query(db);
    query.prepare("SELECT login FROM Person WHERE socketID = :sid");
    query.bindValue(":sid", socketID);
    if (!query.exec() || !query.next()) return "";
    return query.value(0).toString();
}

bool DataBase::logoutUser(const QString& login)
{
    QSqlQuery query(db);
    query.prepare("UPDATE Person SET socketID = NULL WHERE login = :login");
    query.bindValue(":login", login);
    return query.exec();
}

QString DataBase::getStatsByLogin(const QString& login)
{
    QSqlQuery query(db);
    query.prepare("SELECT task1, task2, task3, task4 FROM Person WHERE login = :login");
    query.bindValue(":login", login);
    if (!query.exec() || !query.next())
        return "ERROR user not found";

    return QString("STATS %1: task1=%2 task2=%3 task3=%4 task4=%5")
        .arg(login)
        .arg(query.value(0).toInt())
        .arg(query.value(1).toInt())
        .arg(query.value(2).toInt())
        .arg(query.value(3).toInt());
}
