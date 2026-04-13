#include "mytcpserver.h"
#include "clientworker.h"
#include "database.h"
#include <QThread>

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer(parent)
{
}

bool MyTcpServer::startServer(quint16 port)
{
    if (!DataBase::instance().open()) {
        qDebug() << "Failed to open database";
        return false;
    }

    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "Failed to listen on port" << port;
        return false;
    }

    qDebug() << "Server listening on port" << port;
    return true;
}

void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    // Создаём новый поток и воркер для каждого клиента
    QThread       *thread = new QThread(this);
    ClientWorker  *worker = new ClientWorker(socketDescriptor);

    // Воркер переезжает в новый поток
    worker->moveToThread(thread);

    // Когда поток запустится — вызываем start() у воркера
    connect(thread, &QThread::started,  worker, &ClientWorker::start);

    // Когда воркер завершится — останавливаем и удаляем поток и воркер
    connect(worker, &ClientWorker::finished, thread, &QThread::quit);
    connect(worker, &ClientWorker::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished,      thread, &QObject::deleteLater);

    thread->start();

    qDebug() << "[Server] Spawned new thread for incoming connection. "
                "Active threads:" << QThread::idealThreadCount();
}
