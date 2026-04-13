#ifndef DBCLIENT_H
#define DBCLIENT_H

#include <QTcpSocket>

class DbClient
{
public:
    static DbClient& instance();

    QString send(const QString& query);

private:
    DbClient();
    QTcpSocket socket;
};

#endif
