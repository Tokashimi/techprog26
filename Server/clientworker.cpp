#include "clientworker.h"
#include "database.h"
#include <QStringList>
#include <QDebug>
#include <QThread>   // ← добавить эту строку

ClientWorker::ClientWorker(qintptr socketDescriptor, QObject *parent)
    : QObject(parent)
    , m_socketDescriptor(socketDescriptor)
{
}

// start() вызывается уже внутри нового потока
void ClientWorker::start()
{
    m_socket = new QTcpSocket(this);

    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        qDebug() << "[Worker] Failed to set socket descriptor";
        emit finished();
        return;
    }

    connect(m_socket, &QTcpSocket::readyRead,    this, &ClientWorker::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientWorker::onDisconnected);

    qDebug() << "[Worker] Client connected:" << m_socket->peerAddress().toString()
             << "| Thread:" << QThread::currentThreadId();

    m_socket->write("CONNECTED: Ready for commands\n");
    m_socket->flush();
}

void ClientWorker::onReadyRead()
{
    while (m_socket->canReadLine()) {
        QString line = QString::fromUtf8(m_socket->readLine()).trimmed();
        if (line.isEmpty()) continue;

        qDebug() << "[Worker] Received from"
                 << m_socket->peerAddress().toString() << ":" << line;

        QString response = processCommand(line);
        m_socket->write(response.toUtf8() + "\n");
        m_socket->flush();
    }
}

void ClientWorker::onDisconnected()
{
    qDebug() << "[Worker] Client disconnected:" << m_socket->peerAddress().toString();
    m_socket->deleteLater();
    emit finished();
}

QString ClientWorker::processCommand(const QString &request)
{
    QStringList parts = request.split(' ');
    if (parts.isEmpty()) return "ERROR: empty command";

    QString cmd = parts[0].toUpper();

    // REGISTER <username> <password>
    if (cmd == "REGISTER" && parts.size() == 3) {
        if (DataBase::instance().registerUser(parts[1], parts[2]))
            return "REGISTER OK";
        return "REGISTER FAIL: user may already exist";
    }

    // LOGIN <username> <password>
    if (cmd == "LOGIN" && parts.size() == 3) {
        if (DataBase::instance().loginUser(parts[1], parts[2]))
            return "LOGIN OK";
        return "LOGIN FAIL: invalid credentials";
    }

    // STATS <username>
    if (cmd == "STATS" && parts.size() == 2) {
        return DataBase::instance().getStats(parts[1]);
    }

    // USERS
    if (cmd == "USERS") {
        return DataBase::instance().getAllUsers();
    }

    // HELP
    if (cmd == "HELP") {
        return "Commands: REGISTER <user> <pass> | LOGIN <user> <pass> | STATS <user> | USERS | HELP";
    }

    return "ERROR: unknown command. Type HELP for available commands";
}
