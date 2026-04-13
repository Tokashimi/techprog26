#include "commandprocessor.h"
#include "dbclient.h"
#include <QStringList>
#include <QCryptographicHash>

CommandProcessor::CommandProcessor() {}

QString CommandProcessor::process(const QString &request)
{
    QStringList parts = request.split(':');
    QString command = parts[0].toLower();

    QString payload = (parts.size() > 1) ? parts[1] : "";

    if (command == "login")
        return cmdLogin(payload);

    if (command == "register")
        return cmdRegister(payload);

    if (command == "stats")
        return cmdStats();

    if (command == "hash")
        return cmdHash(payload);

    return "ERROR: unknown command";
}

QString CommandProcessor::cmdRegister(const QString &data)
{
    QStringList p = data.split(',');
    if (p.size() != 2) return "ERR";

    QString login = p[0];
    QString pass = p[1];

    QString hash = QCryptographicHash::hash(pass.toUtf8(),
                                            QCryptographicHash::Sha256).toHex();

    QString query = QString("INSERT INTO users(login,password) VALUES('%1','%2');")
                        .arg(login, hash);

    return DbClient::instance().send(query);
}

QString CommandProcessor::cmdLogin(const QString &data)
{
    QStringList p = data.split(',');
    if (p.size() != 2) return "ERR";

    QString login = p[0];
    QString pass = p[1];

    QString hash = QCryptographicHash::hash(pass.toUtf8(),
                                            QCryptographicHash::Sha256).toHex();

    QString query = QString(
                        "SELECT login FROM users WHERE login='%1' AND password='%2';")
                        .arg(login, hash);

    QString result = DbClient::instance().send(query);

    if (result.contains(login))
        return "LOGIN OK";

    return "LOGIN FAIL";
}

QString CommandProcessor::cmdStats()
{
    return DbClient::instance().send("SELECT COUNT(*) FROM users;");
}

QString CommandProcessor::cmdHash(const QString &data)
{
    QByteArray hash = QCryptographicHash::hash(data.toUtf8(),
                                               QCryptographicHash::Sha256);
    return hash.toHex();
}
