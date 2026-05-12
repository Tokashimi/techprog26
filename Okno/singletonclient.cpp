#include "singletonclient.h"
#include <QCryptographicHash>
#include <QDebug>

SingletonClient*   SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;

SingletonClient::SingletonClient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("192.168.1.136", 33333);

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

bool SingletonClient::isConnected() const
{
    return mTcpSocket->state() == QAbstractSocket::ConnectedState;
}

QString SingletonClient::send_msg_to_server(QString query)
{
    if (!isConnected()) {
        mTcpSocket->connectToHost("192.168.1.136", 33333);
        if (!mTcpSocket->waitForConnected(3000)) {
            return "ERROR no connection";
        }
    }

    mTcpSocket->write(query.toUtf8());
    mTcpSocket->waitForReadyRead(5000);

    QString msg = "";
    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }
    qDebug() << "[SingletonClient] ←" << msg;
    return msg.trimmed();
}

void SingletonClient::slotDisconnected()
{
    qDebug() << "Сервер отключился";
}
