#include "singletonclient.h"
#include <QDebug>

// Определение статических членов класса (обязательно в .cpp)
SingletonClient*   SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;

// Конструктор - запрос на подключение к серверу
SingletonClient::SingletonClient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333); // подключаемся к серверу

    // Когда пришли данные от сервера - читаем их в slotServerRead
    connect(mTcpSocket, SIGNAL(readyRead()),
            this, SLOT(slotServerRead()));

    // Когда сервер отключился - вызываем slotDisconnected
    connect(mTcpSocket, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
}

// Деструктор - отключение от сервера
SingletonClient::~SingletonClient()
{
    mTcpSocket->disconnectFromHost();
}

// Единственная точка доступа к синглтону
SingletonClient* SingletonClient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new SingletonClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

// Отправка сообщения на сервер - функция
void SingletonClient::send_msg_to_server(QString query)
{
    mTcpSocket->write(query.toUtf8());
}

// Обработка сообщений от сервера - слот
void SingletonClient::slotServerRead()
{
    QString msg = "";
    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }
    qDebug() << msg;
    emit message_from_server(msg);
}

// Отключение при отключении сервера
void SingletonClient::slotDisconnected()
{
    qDebug() << "Сервер отключился";
}
