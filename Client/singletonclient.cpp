#include "singletonclient.h"
#include <QDebug>

SingletonClient*   SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;

SingletonClient::SingletonClient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
}

SingletonClient::~SingletonClient()
{
    mTcpSocket->disconnectFromHost();
}

SingletonClient* SingletonClient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new SingletonClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

QString SingletonClient::send_msg_to_server(QString query)
{
    mTcpSocket->write(query.toUtf8());

    mTcpSocket->waitForReadyRead();

    QString msg = "";
    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }
    qDebug() << msg;
    return msg;
}

void SingletonClient::slotDisconnected()
{
    qDebug() << "Сервер отключился";
}
