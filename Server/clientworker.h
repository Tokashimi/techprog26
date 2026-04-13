#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
#include <QTcpSocket>

// ClientWorker живёт в отдельном потоке и обслуживает одного клиента.
// MyTcpServer создаёт его через QThread для каждого входящего соединения.
class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(qintptr socketDescriptor, QObject *parent = nullptr);

public slots:
    // Вызывается сразу после перемещения в поток
    void start();

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QString processCommand(const QString &request);

    qintptr     m_socketDescriptor;
    QTcpSocket *m_socket = nullptr;

signals:
    void finished(); // поток может завершиться после этого сигнала
};

#endif // CLIENTWORKER_H
