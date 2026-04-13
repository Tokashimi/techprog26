#include "database.h"
#include <QMutexLocker>

DataBase& DataBase::instance()
{
    static DataBase inst;
    return inst;
}

bool DataBase::open()
{
    QMutexLocker locker(&m_mutex);

    if (m_db.isOpen()) return true;

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("server.db");

    if (!m_db.open()) {
        qDebug() << "Database open error:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS users "
                    "(username TEXT PRIMARY KEY, password TEXT)")) {
        qDebug() << "Table creation error:" << query.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully";
    return true;
}

bool DataBase::registerUser(const QString& username, const QString& password)
{
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO users (username, password) VALUES (:u, :p)");
    query.bindValue(":u", username);
    query.bindValue(":p", password);

    if (!query.exec()) {
        qDebug() << "Register error:" << query.lastError().text();
        return false;
    }

    qDebug() << "User registered:" << username;
    return true;
}

bool DataBase::loginUser(const QString& username, const QString& password)
{
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare("SELECT password FROM users WHERE username = :u");
    query.bindValue(":u", username);

    if (!query.exec()) {
        qDebug() << "Login query error:" << query.lastError().text();
        return false;
    }

    if (query.next())
        return query.value(0).toString() == password;

    return false;
}

QString DataBase::getStats(const QString& username)
{
    QMutexLocker locker(&m_mutex);

    QSqlQuery query(m_db);
    query.prepare("SELECT COUNT(*) FROM users");
    query.exec();

    int total = 0;
    if (query.next())
        total = query.value(0).toInt();

    return QString("STATS: user=%1, total_users=%2").arg(username).arg(total);
}

QString DataBase::getAllUsers()
{
    QMutexLocker locker(&m_mutex);

    QSqlQuery query("SELECT username FROM users", m_db);
    QStringList users;
    while (query.next())
        users << query.value(0).toString();

    return "USERS: " + users.join(", ");
}
