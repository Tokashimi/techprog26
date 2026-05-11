#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class SingletonClient;

// destroyer
class SingletonDestroyer
{
private:
    SingletonClient* p_instance;
public:
    ~SingletonDestroyer() { delete p_instance; }
    void initialize(SingletonClient* p) { p_instance = p; }
};

class SingletonClient : public QObject
{
    Q_OBJECT
private:
    static SingletonClient*   p_instance;
    static SingletonDestroyer destroyer;
    QTcpSocket* mTcpSocket;

protected:
    explicit SingletonClient(QObject* parent = nullptr);
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;
    ~SingletonClient();
    friend class SingletonDestroyer;

public:
    static SingletonClient* getInstance(); //единственный способ доступа

    QString send_msg_to_server(QString query); // отправка сообщений на сервер

private slots:
    void slotDisconnected(); // отключение при отключении сервера
};

#endif // SINGLETONCLIENT_H
