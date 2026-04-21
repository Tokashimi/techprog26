#include <QCoreApplication>
#include <QThread>
#include <QMetaObject>
#include "singletonclient.h"
#include <iostream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Создаём синглтон - он сразу подключается к серверу в конструкторе
    SingletonClient::getInstance();

    // Читаем ввод в отдельном потоке
    QThread* inputThread = new QThread();
    QObject::connect(inputThread, &QThread::started, [&a]()
    {
        std::string msg;
        while (true)
        {
            std::getline(std::cin, msg);
            if (msg == "exit") { a.quit(); break; }
            if (!msg.empty())
            {
                QString qmsg = QString::fromStdString(msg) + "\n";
                // Вызываем send_msg_to_server в главном потоке через invokeMethod
                QMetaObject::invokeMethod(SingletonClient::getInstance(),
                    "send_msg_to_server",
                    Qt::QueuedConnection,
                    Q_ARG(QString, qmsg));
            }
        }
    });
    inputThread->start();

    return a.exec();
}
