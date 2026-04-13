#include <QCoreApplication>
#include "mytcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
    if (!server.startServer(33333)) {
        qDebug() << "Failed to start server!";
        return 1;
    }

    qDebug() << "Server started on port 33333";
    qDebug() << "Each client is handled in its own thread.";
    qDebug() << "";
    qDebug() << "Available commands:";
    qDebug() << "  REGISTER <username> <password>";
    qDebug() << "  LOGIN    <username> <password>";
    qDebug() << "  STATS    <username>";
    qDebug() << "  USERS";
    qDebug() << "  HELP";

    return a.exec();
}
