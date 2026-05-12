/**
 * \file singletonclient.h
 * \brief Объявление классов SingletonClient и SingletonDestroyer — синхронного TCP-клиента.
 */
#ifndef SINGLETONCLIENT_H
#define SINGLETONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class SingletonClient;

/**
 * \class SingletonDestroyer
 * \brief Вспомогательный класс для корректного удаления SingletonClient.
 *
 * Уничтожает единственный экземпляр SingletonClient при завершении программы.
 */
class SingletonDestroyer
{
private:
    SingletonClient* p_instance;
public:
    ~SingletonDestroyer() { delete p_instance; }

    /**
     * \brief Запоминает указатель на управляемый синглтон.
     * \param p Указатель на экземпляр SingletonClient.
     */
    void initialize(SingletonClient* p) { p_instance = p; }
};

/**
 * \class SingletonClient
 * \brief Синхронный TCP-клиент для связи с сервером (паттерн Singleton).
 *
 * Подключается к серверу при первом обращении через getInstance().
 * Все запросы выполняются блокирующе: send_msg_to_server() отправляет
 * команду и ожидает ответа до 5 секунд.
 *
 * \note Устаревший клиент — для новых функций рекомендуется использовать ClientApi.
 */
class SingletonClient : public QObject
{
    Q_OBJECT
private:
    static SingletonClient*   p_instance; ///< Единственный экземпляр.
    static SingletonDestroyer destroyer;  ///< Управляет временем жизни экземпляра.
    QTcpSocket* mTcpSocket;               ///< TCP-сокет соединения.

protected:
    explicit SingletonClient(QObject* parent = nullptr);
    SingletonClient(SingletonClient&) = delete;
    SingletonClient& operator=(SingletonClient&) = delete;
    ~SingletonClient();
    friend class SingletonDestroyer;

public:
    /**
     * \brief Возвращает единственный экземпляр клиента.
     *
     * При первом вызове создаёт объект и устанавливает TCP-соединение с сервером.
     * \return Указатель на экземпляр SingletonClient.
     */
    static SingletonClient* getInstance();

    /**
     * \brief Отправляет команду на сервер и блокирующе ожидает ответа.
     *
     * Если соединение разорвано, пытается переподключиться (таймаут 3 с).
     * После подключения отправляет запрос и ждёт данных до 5 секунд.
     * \param query Строка команды (например, "LOGIN user pass").
     * \return Ответ сервера, или "ERROR no connection" при ошибке подключения.
     */
    QString send_msg_to_server(QString query);

    /**
     * \brief Возвращает состояние TCP-соединения.
     * \return true если сокет находится в состоянии ConnectedState.
     */
    bool isConnected() const;

private slots:
    /**
     * \brief Слот: выводит в лог сообщение об отключении от сервера.
     */
    void slotDisconnected();
};

#endif
