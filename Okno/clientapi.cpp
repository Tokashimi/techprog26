#include "clientapi.h"
#include <QCryptographicHash>
#include <QDebug>

// ── Хеширование (SHA-256, как на сервере) ────────────────────────────────────
static QString hashPassword(const QString &password)
{
    return QCryptographicHash::hash(
               password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

// ── Конструктор ──────────────────────────────────────────────────────────────
ClientApi::ClientApi(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket(this))
{
    connect(m_socket, &QTcpSocket::readyRead,
            this, &ClientApi::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected,
            this, &ClientApi::onDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred,
            this, &ClientApi::onSocketError);
    connect(m_socket, &QTcpSocket::connected,
            this, [this]() { m_reconnectTimer.stop(); });

    m_reconnectTimer.setInterval(10000);
    m_reconnectTimer.setSingleShot(false);
    connect(&m_reconnectTimer, &QTimer::timeout,
            this, &ClientApi::onReconnectTimeout);
}

// ── Подключение к серверу ────────────────────────────────────────────────────
void ClientApi::connectToServer(const QString &host, quint16 port)
{
    m_host = host;
    m_port = port;

    if (m_socket->state() == QAbstractSocket::ConnectedState ||
        m_socket->state() == QAbstractSocket::ConnectingState)
        return;

    m_socket->abort();
    m_socket->connectToHost(host, port);
}

bool ClientApi::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

// ── Отправка сырой строки ────────────────────────────────────────────────────
void ClientApi::sendRaw(const QString &msg)
{
    if (!isConnected()) {
        emit errorOccurred(tr("Нет соединения с сервером"));
        scheduleReconnect();
        return;
    }
    qDebug() << "[ClientApi] →" << msg;
    m_socket->write(msg.toUtf8());
    m_socket->flush();
}

// ── Высокоуровневые запросы ──────────────────────────────────────────────────
// Сервер ожидает: "LOGIN login password" (пароль — SHA-256 hex)
void ClientApi::sendLogin(const QString &login, const QString &password)
{
    m_currentLogin = login;   // сохраняем для последующих STATS-запросов
    sendRaw(QString("LOGIN %1 %2").arg(login, hashPassword(password)));
}

// Сервер ожидает: "REGISTER login password" (пароль — SHA-256 hex)
void ClientApi::sendRegister(const QString &login, const QString &password)
{
    sendRaw(QString("REGISTER %1 %2").arg(login, hashPassword(password)));
}

// Сервер ожидает: "STATS login"
void ClientApi::sendStats(const QString &login)
{
    sendRaw(QString("STATS %1").arg(login));
}

// Сервер ожидает: "LOGOUT"
void ClientApi::sendLogout()
{
    sendRaw("LOGOUT");
}

// ── Приём данных ─────────────────────────────────────────────────────────────
void ClientApi::onReadyRead()
{
    m_buffer += QString::fromUtf8(m_socket->readAll());

    QString msg = m_buffer.trimmed();
    if (!msg.isEmpty()) {
        processResponse(msg);
        m_buffer.clear();
    }
}

void ClientApi::onDisconnected()
{
    emit disconnected();
    scheduleReconnect();
}

void ClientApi::onSocketError(QAbstractSocket::SocketError /*error*/)
{
    emit errorOccurred(m_socket->errorString());
    scheduleReconnect();
}

void ClientApi::scheduleReconnect()
{
    if (m_host.isEmpty() || m_port == 0) return;
    if (!m_reconnectTimer.isActive()) m_reconnectTimer.start();
}

void ClientApi::onReconnectTimeout()
{
    if (m_socket->state() == QAbstractSocket::ConnectedState ||
        m_socket->state() == QAbstractSocket::ConnectingState)
        return;
    m_socket->abort();
    m_socket->connectToHost(m_host, m_port);
}

// ── Парсинг ответа сервера ───────────────────────────────────────────────────
// Протокол сервера (techprog26):
//   "OK logged in"
//   "OK registered"
//   "OK logged out"
//   "ERROR <причина>"
//   "STATS login: task1=N task2=N task3=N task4=N"
ParsedResponse ClientApi::parseResponse(const QString &msg)
{
    ParsedResponse r;
    QString s = msg.trimmed();

    if (s == "OK logged in") {
        r.type = ResponseType::AuthOk;
        return r;
    }
    if (s == "OK registered") {
        r.type = ResponseType::RegOk;
        return r;
    }
    if (s == "OK logged out") {
        r.type = ResponseType::LogoutOk;
        return r;
    }
    if (s.startsWith("STATS ")) {
        // "STATS login: task1=N task2=N task3=N task4=N"
        r.type = ResponseType::StatsOk;

        // Извлекаем логин (между "STATS " и ":")
        int colonPos = s.indexOf(':');
        if (colonPos != -1) {
            r.login = s.mid(6, colonPos - 6).trimmed();
        }

        // Извлекаем значения task1..task4
        auto extractInt = [&](const QString &key) -> int {
            int idx = s.indexOf(key + "=");
            if (idx == -1) return 0;
            int start = idx + key.length() + 1;
            int end = s.indexOf(' ', start);
            QString val = (end == -1) ? s.mid(start) : s.mid(start, end - start);
            return val.toInt();
        };

        r.t1 = extractInt("task1");
        r.t2 = extractInt("task2");
        r.t3 = extractInt("task3");
        r.t4 = extractInt("task4");
        return r;
    }
    if (s.startsWith("ERROR ")) {
        r.message = s.mid(6).trimmed();
        // Определяем контекст по тексту ошибки
        if (r.message == "wrong login or password") {
            r.type = ResponseType::AuthError;
        } else if (r.message == "login already taken" ||
                   r.message == "registration failed") {
            r.type = ResponseType::RegError;
        } else if (r.message == "not logged in") {
            r.type = ResponseType::LogoutError;
        } else if (r.message == "user not found") {
            r.type = ResponseType::StatsError;
        } else {
            // Неизвестная ошибка — возвращаем как Unknown с текстом
            r.type = ResponseType::Unknown;
        }
        return r;
    }

    r.type = ResponseType::Unknown;
    r.message = s;
    return r;
}

void ClientApi::processResponse(const QString &msg)
{
    qDebug() << "[ClientApi] ←" << msg;
    ParsedResponse r = parseResponse(msg);

    switch (r.type) {
    case ResponseType::AuthOk:
        emit authResult(true, {});
        break;
    case ResponseType::AuthError:
        emit authResult(false, r.message.isEmpty()
                                   ? tr("Неверный логин или пароль")
                                   : r.message);
        break;
    case ResponseType::RegOk:
        emit regResult(true, {});
        break;
    case ResponseType::RegError:
        emit regResult(false, r.message.isEmpty()
                                  ? tr("Ошибка регистрации")
                                  : r.message);
        break;
    case ResponseType::StatsOk:
        emit statsResult(r.login, r.t1, r.t2, r.t3, r.t4);
        break;
    case ResponseType::StatsError:
        emit errorOccurred(tr("Статистика: ") + r.message);
        break;
    case ResponseType::LogoutOk:
        emit logoutResult(true, {});
        break;
    case ResponseType::LogoutError:
        emit logoutResult(false, r.message.isEmpty()
                                     ? tr("Ошибка выхода")
                                     : r.message);
        break;
    default:
        emit errorOccurred(tr("Неизвестный ответ сервера: %1").arg(msg));
        break;
    }
}
