#include <QCoreApplication>
#include <QDebug>
#include "mytcpserver.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Инициализируем базу данных через синглтон
    if (!DataBase::getInstance()->init("timp.db")) {
        qDebug() << "Не удалось открыть БД. Завершение.";
        return 1;
    }

    // Запускаем сервер (он сам слушает порт в конструкторе)
    MyTcpServer server;

    return a.exec();
}