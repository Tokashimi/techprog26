/**
 * \file mytcpserver.h
 * \brief Объявление класса MyTcpServer — TCP-сервера приложения.
 */
#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QDebug>

/**
 * \class MyTcpServer
 * \brief TCP-сервер, принимающий подключения клиентов и обрабатывающий их запросы.
 *
 * При запуске начинает слушать порт 33333 на всех интерфейсах.
 * Каждый входящий запрос передаётся в функцию parsing(), которая
 * маршрутизирует команды (LOGIN, REGISTER, STATS, TASK*, ANSWER, LOGOUT)
 * и возвращает строку-ответ клиенту.
 */
class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт сервер и начинает прослушивать порт 33333.
     * \param parent Родительский объект Qt.
     */
    explicit MyTcpServer(QObject *parent = nullptr);

    /**
     * \brief Останавливает сервер и освобождает ресурсы.
     */
    ~MyTcpServer();

public slots:
    /**
     * \brief Слот: принимает новое входящее подключение.
     *
     * Добавляет сокет в список активных клиентов и подключает
     * сигналы readyRead / disconnected к соответствующим слотам.
     */
    void slotNewConnection();

    /**
     * \brief Слот: удаляет отключившийся сокет из списка клиентов.
     */
    void slotClientDisconnected();

    /**
     * \brief Слот: читает входящие данные от клиента и отправляет ответ.
     *
     * Считывает строку запроса, вызывает parsing() и отправляет
     * полученный ответ обратно клиенту.
     */
    void slotServerRead();

private:
    QTcpServer*        mTcpServer; ///< Внутренний Qt TCP-сервер.
    QList<QTcpSocket*> mClients;   ///< Список активных клиентских сокетов.
};

#endif
