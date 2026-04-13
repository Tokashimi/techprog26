#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <QString>

class CommandProcessor
{
public:
    CommandProcessor();

    QString process(const QString& request);

private:
    QString cmdLogin(const QString& data);
    QString cmdRegister(const QString& data);
    QString cmdStats();
    QString cmdHash(const QString& data);
};

#endif
