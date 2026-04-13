#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QString>

class RequestHandler
{
public:
    QString processRequest(const QString& request);
};

#endif // REQUESTHANDLER_H
