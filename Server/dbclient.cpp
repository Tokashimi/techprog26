#include "dbclient.h"
#include <QTcpSocket>
DbClient::DbClient() {}

DbClient& DbClient::instance()
{
    static DbClient inst;
    return inst;
}

QString DbClient::send(const QString &query)
{
    if (socket.state() != QAbstractSocket::ConnectedState) {
        socket.connectToHost("127.0.0.1", 40000);
        if (!socket.waitForConnected(2000))
            return "DB ERROR";
    }

    socket.write(query.toUtf8() + "\n");
    socket.waitForBytesWritten();

    socket.waitForReadyRead();

    QByteArray data = socket.readAll();
    return QString::fromUtf8(data);
}
