/**
 * \file clientapi.h
 * \brief Объявление асинхронного API-клиента ClientApi для взаимодействия с сервером.
 */
#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

/**
 * \enum ResponseType
 * \brief Типы ответов, распознаваемых от сервера.
 */
enum class ResponseType {
    AuthOk,      ///< "OK logged in" — авторизация прошла успешно.
    AuthError,   ///< "ERROR wrong login or password".
    RegOk,       ///< "OK registered" — регистрация прошла успешно.
    RegError,    ///< "ERROR login already taken" / "ERROR registration failed".
    StatsOk,     ///< "STATS login: task1=N task2=N task3=N task4=N".
    StatsError,  ///< "ERROR user not found".
    LogoutOk,    ///< "OK logged out".
    LogoutError, ///< "ERROR not logged in".
    Unknown      ///< Нераспознанный ответ сервера.
};

/**
 * \struct ParsedResponse
 * \brief Разобранный ответ от сервера.
 */
struct ParsedResponse {
    ResponseType type = ResponseType::Unknown; ///< Тип ответа.
    QString message;  ///< Текст сообщения (заполняется для ошибок).
    QString login;    ///< Логин пользователя (заполняется для StatsOk).
    int t1 = 0;       ///< Счётчик задания 1 (заполняется для StatsOk).
    int t2 = 0;       ///< Счётчик задания 2 (заполняется для StatsOk).
    int t3 = 0;       ///< Счётчик задания 3 (заполняется для StatsOk).
    int t4 = 0;       ///< Счётчик задания 4 (заполняется для StatsOk).
};

/**
 * \class ClientApi
 * \brief Асинхронный TCP-клиент с автоматическим переподключением.
 *
 * Предоставляет высокоуровневый интерфейс для работы с сервером:
 * отправка команд через методы sendLogin(), sendRegister(), sendStats(), sendLogout().
 * Результат каждой операции возвращается через соответствующий Qt-сигнал.
 *
 * При разрыве соединения автоматически повторяет попытку подключения каждые 10 секунд.
 */
class ClientApi : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт объект и подключает внутренние сигналы сокета.
     * \param parent Родительский объект Qt.
     */
    explicit ClientApi(QObject *parent = nullptr);

    /**
     * \brief Устанавливает TCP-соединение с сервером.
     *
     * Повторный вызов при уже установленном соединении игнорируется.
     * \param host Адрес сервера (IP или hostname).
     * \param port Порт сервера.
     */
    void connectToServer(const QString &host, quint16 port);

    /**
     * \brief Возвращает состояние соединения.
     * \return true если соединение установлено.
     */
    bool isConnected() const;

    /**
     * \brief Отправляет команду LOGIN на сервер.
     *
     * Пароль хэшируется SHA-256 перед отправкой.
     * Результат приходит через сигнал authResult().
     * \param login    Логин пользователя.
     * \param password Пароль в открытом виде.
     */
    void sendLogin(const QString &login, const QString &password);

    /**
     * \brief Отправляет команду REGISTER на сервер.
     *
     * Пароль хэшируется SHA-256 перед отправкой.
     * Результат приходит через сигнал regResult().
     * \param login    Желаемый логин.
     * \param password Пароль в открытом виде.
     */
    void sendRegister(const QString &login, const QString &password);

    /**
     * \brief Отправляет команду STATS на сервер.
     *
     * Результат приходит через сигнал statsResult().
     * \param login Логин пользователя, чья статистика запрашивается.
     */
    void sendStats(const QString &login);

    /**
     * \brief Отправляет команду LOGOUT на сервер.
     *
     * Результат приходит через сигнал logoutResult().
     */
    void sendLogout();

    /**
     * \brief Устанавливает текущий логин для внутреннего использования.
     * \param login Логин авторизованного пользователя.
     */
    void setCurrentLogin(const QString &login) { m_currentLogin = login; }

    /**
     * \brief Возвращает текущий сохранённый логин.
     * \return Логин авторизованного пользователя.
     */
    QString currentLogin() const { return m_currentLogin; }

signals:
    /**
     * \brief Результат авторизации (ответ на sendLogin()).
     * \param ok      true если авторизация прошла успешно.
     * \param message Текст ошибки (пустой при успехе).
     */
    void authResult(bool ok, const QString &message);

    /**
     * \brief Результат регистрации (ответ на sendRegister()).
     * \param ok      true если регистрация прошла успешно.
     * \param message Текст ошибки (пустой при успехе).
     */
    void regResult(bool ok, const QString &message);

    /**
     * \brief Статистика пользователя получена (ответ на sendStats()).
     * \param login Логин пользователя.
     * \param t1    Счётчик задания 1.
     * \param t2    Счётчик задания 2.
     * \param t3    Счётчик задания 3.
     * \param t4    Счётчик задания 4.
     */
    void statsResult(const QString &login, int t1, int t2, int t3, int t4);

    /**
     * \brief Результат выхода из системы (ответ на sendLogout()).
     * \param ok      true если выход прошёл успешно.
     * \param message Текст ошибки (пустой при успехе).
     */
    void logoutResult(bool ok, const QString &message);

    /**
     * \brief Возникла ошибка соединения или протокола.
     * \param message Описание ошибки.
     */
    void errorOccurred(const QString &message);

    /**
     * \brief Соединение с сервером разорвано.
     */
    void disconnected();

private slots:
    void onReadyRead();
    void onDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onReconnectTimeout();

private:
    void sendRaw(const QString &msg);
    void processResponse(const QString &msg);
    void scheduleReconnect();
    static ParsedResponse parseResponse(const QString &msg);

    QTcpSocket *m_socket;         ///< TCP-сокет соединения.
    QString     m_buffer;         ///< Буфер входящих данных.
    QString     m_currentLogin;   ///< Логин текущего пользователя.
    QTimer      m_reconnectTimer; ///< Таймер автопереподключения (интервал 10 с).
    QString     m_host;           ///< Адрес сервера.
    quint16     m_port = 0;       ///< Порт сервера.
};

#endif // CLIENTAPI_H
