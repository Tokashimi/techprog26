#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QDebug>

// MyTcpServer только принимает входящие соединения.
// Каждый клиент передаётся в отдельный ClientWorker, который
// запускается в собственном QThread — истинная параллельная обработка.
class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    bool startServer(quint16 port);

protected:
    // Переопределяем: здесь создаём поток + воркер для нового клиента
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // MYTCPSERVER_H
