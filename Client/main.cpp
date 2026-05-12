#include <QCoreApplication>
#include "singletonclient.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SingletonClient::getInstance();

    std::string msg;
    while (true)
    {
        std::getline(std::cin, msg);
        if (msg == "exit") break;
        if (!msg.empty())
            SingletonClient::getInstance()->send_msg_to_server(QString::fromStdString(msg));
    }

    return a.exec();
}
