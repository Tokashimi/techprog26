#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class SingletonClient;

// Destroyer — автоматически удаляет синглтон при завершении программы
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
    static SingletonClient* getInstance();

    // Отправить команду на сервер и получить ответ синхронно
    QString send_msg_to_server(QString query);

    bool isConnected() const;

private slots:
    void slotDisconnected();
};

#endif // SINGLETONCLIENT_H

