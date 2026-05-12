#include "mytcpserver.h"
#include "functions.h"
#include "database.h"
#include <QDebug>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);
    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

MyTcpServer::~MyTcpServer()
{
    mTcpServer->close();
}

void MyTcpServer::slotNewConnection()
{
    QTcpSocket* socket = mTcpServer->nextPendingConnection();
    mClients.append(socket);
    socket->write("Hello, World!!! I am echo server!\r\n");
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;
    QByteArray data = socket->readAll();
    QString request = QString::fromUtf8(data).trimmed();
    qDebug() << "Запрос от" << socket->socketDescriptor() << ":" << request;
    QString socketID = QString::number(socket->socketDescriptor());
    QString response = parsing(request, socketID);
    socket->write(response.toUtf8());
    socket->flush();
}

void MyTcpServer::slotClientDisconnected()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    mClients.removeOne(socket);
    socket->close();
}
