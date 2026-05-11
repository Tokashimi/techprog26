#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

// ── Типы ответов от сервера ──────────────────────────────────────────────────
enum class ResponseType {
    AuthOk,       // "OK logged in"
    AuthError,    // "ERROR wrong login or password"
    RegOk,        // "OK registered"
    RegError,     // "ERROR login already taken" / "ERROR registration failed"
    StatsOk,      // "STATS login: task1=N task2=N task3=N task4=N"
    StatsError,   // "ERROR user not found"
    LogoutOk,     // "OK logged out"
    LogoutError,  // "ERROR not logged in"
    Unknown
};

struct ParsedResponse {
    ResponseType type = ResponseType::Unknown;
    QString message;

    // для StatsOk
    QString login;
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
};

// ── API-класс ────────────────────────────────────────────────────────────────
class ClientApi : public QObject
{
    Q_OBJECT
public:
    explicit ClientApi(QObject *parent = nullptr);

    void connectToServer(const QString &host, quint16 port);
    bool isConnected() const;

    // высокоуровневые запросы (соответствуют командам сервера)
    void sendLogin   (const QString &login, const QString &password);
    void sendRegister(const QString &login, const QString &password);
    void sendStats   (const QString &login);
    void sendLogout  ();

    // текущий логин (для запроса статистики)
    void setCurrentLogin(const QString &login) { m_currentLogin = login; }
    QString currentLogin() const               { return m_currentLogin; }

signals:
    void authResult   (bool ok, const QString &message);
    void regResult    (bool ok, const QString &message);
    void statsResult  (const QString &login, int t1, int t2, int t3, int t4);
    void logoutResult (bool ok, const QString &message);
    void errorOccurred(const QString &message);
    void disconnected ();

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

    QTcpSocket *m_socket;
    QString     m_buffer;
    QString     m_currentLogin;

    QTimer  m_reconnectTimer;
    QString m_host;
    quint16 m_port = 0;
};

#endif // CLIENTAPI_H
