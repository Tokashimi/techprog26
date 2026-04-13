#include "sqlserver.h"
#include <QSqlQuery>
#include <QSqlError>

SqlServer::SqlServer(quint16 port, QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();

    QSqlQuery q;
    q.exec("CREATE TABLE IF NOT EXISTS users("
           "login TEXT PRIMARY KEY,"
           "password TEXT)");

    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection,
            this, &SqlServer::newConnection);

    server->listen(QHostAddress::Any, port);
}

void SqlServer::newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead,
            this, &SqlServer::readData);
}

void SqlServer::readData()
{
    QByteArray data = socket->readAll();
    QString sql = QString::fromUtf8(data).trimmed();

    QSqlQuery q;
    if (!q.exec(sql)) {
        socket->write("ERROR\n");
        return;
    }

    QString result;

    while (q.next()) {
        result += q.value(0).toString() + "\n";
    }

    socket->write(result.toUtf8());
}
