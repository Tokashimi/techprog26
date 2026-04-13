#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMutex>
#include <QDebug>

// DataBase — потокобезопасный синглтон.
// QMutex защищает все операции с базой данных,
// так как несколько ClientWorker из разных потоков обращаются сюда одновременно.
class DataBase
{
public:
    static DataBase& instance();

    bool    open();
    bool    registerUser(const QString& username, const QString& password);
    bool    loginUser(const QString& username, const QString& password);
    QString getStats(const QString& username);
    QString getAllUsers();

private:
    DataBase() = default;

    QSqlDatabase m_db;
    QMutex       m_mutex; // защита от одновременного доступа из нескольких потоков
};

#endif // DATABASE_H
