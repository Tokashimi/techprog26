#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class SingletonClient;

// Destroyer - автоматически удаляет синглтон при завершении программы
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
    static SingletonClient*   p_instance; // единственный экземпляр
    static SingletonDestroyer destroyer;  // удалит экземпляр при выходе
    QTcpSocket* mTcpSocket;               // сокет для связи с сервером

protected:
    explicit SingletonClient(QObject* parent = nullptr); // запрос на подключение - в конструкторе
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;
    ~SingletonClient(); // отключение - в деструкторе
    friend class SingletonDestroyer;

public:
    static SingletonClient* getInstance(); // единственная точка доступа к объекту

    Q_INVOKABLE void send_msg_to_server(QString query); // отправка сообщений на сервер - функция

signals:
    void message_from_server(QString msg); // сигнал при получении ответа от сервера

private slots:
    void slotServerRead();   // обработка сообщений от сервера - слот
    void slotDisconnected(); // отключение при отключении сервера
};

#endif // SINGLETONCLIENT_H
