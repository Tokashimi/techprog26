#include "singletonclient.h"
#include <QDebug>

SingletonClient*   SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;

//запрос на подключение к серверу
SingletonClient::SingletonClient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("192.168.1.136", 33333); // подключение

    // при отключении - выключаем
    connect(mTcpSocket, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
}

// Деструктор
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

// отправка сообщения на сервер
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

// отключение при отключении сервера
void SingletonClient::slotDisconnected()
{
    qDebug() << "Сервер отключился";
}
