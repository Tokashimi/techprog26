#include "mytcpserver.h"
#include "functions.h"
#include "database.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "Сервер не запустился:" << mTcpServer->errorString();
    } else {
        qDebug() << "Сервер запущен на порту 33333";
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

    connect(socket, &QTcpSocket::readyRead,
            this, &MyTcpServer::slotServerRead);
    connect(socket, &QTcpSocket::disconnected,
            this, &MyTcpServer::slotClientDisconnected);

    qDebug() << "Новый клиент подключён, сокет:" << socket->socketDescriptor();
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
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QString socketID = QString::number(socket->socketDescriptor());

    QString login = DataBase::getInstance()->getLoginBySocket(socketID);
    if (!login.isEmpty()) {
        DataBase::getInstance()->logoutUser(login);
        qDebug() << "Авто-logout для:" << login;
    }

    mClients.removeAll(socket);
    socket->deleteLater();
    qDebug() << "Клиент отключился:" << socketID;
}
