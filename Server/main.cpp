#include <QCoreApplication>
#include <QDebug>
#include "mytcpserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (!DataBase::getInstance()->init("timp.db")) {
        qDebug() << "Не удалось открыть БД. Завершение.";
        return 1;
    }

    MyTcpServer server;

    return a.exec();
}
