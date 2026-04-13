#ifndef SQLSERVER_H
#define SQLSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>

class SqlServer : public QObject
{
    Q_OBJECT
public:
    explicit SqlServer(quint16 port = 40000, QObject *parent = nullptr);

private slots:
    void newConnection();
    void readData();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    QSqlDatabase db;
};

#endif
