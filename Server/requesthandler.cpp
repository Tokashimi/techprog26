#include "requesthandler.h"
#include "database.h"
#include <QStringList>

QString RequestHandler::processRequest(const QString& request)
{
    QStringList parts = request.split(" ");
    if (parts.isEmpty()) return "ERROR: empty command";

    QString cmd = parts[0].toUpper();

    if (cmd == "REGISTER" && parts.size() == 3) {
        if (DataBase::instance().registerUser(parts[1], parts[2]))
            return "REGISTER OK";
        return "REGISTER FAIL";
    }

    if (cmd == "LOGIN" && parts.size() == 3) {
        if (DataBase::instance().loginUser(parts[1], parts[2]))
            return "LOGIN OK";
        return "LOGIN FAIL";
    }

    if (cmd == "STATS" && parts.size() == 2) {
        return DataBase::instance().getStats(parts[1]);
    }

    if (cmd == "LOGOUT") return "LOGOUT OK";

    return "ERROR: unknown command";
}
