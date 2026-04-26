#include "functions.h"
#include "database.h"
#include <QCryptographicHash>

static QString hashPassword(const QString& password)
{
    return QCryptographicHash::hash(
               password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

QString parsing(const QString& str, const QString& socketID)
{
    QStringList parts = str.trimmed().split(" ", Qt::SkipEmptyParts);
    if (parts.isEmpty()) return "ERROR unknown command";

    QString cmd = parts[0].toUpper();
    parts.removeFirst();

    qDebug() << "[Server] Команда:" << cmd << "| Параметры:" << parts;

    // REGISTER login password
    if (cmd == "REGISTER") {
        if (parts.size() < 2) return "ERROR need: REGISTER login password";
        if (DataBase::getInstance()->loginExists(parts[0]))
            return "ERROR login already taken";
        if (DataBase::getInstance()->registerUser(parts[0], hashPassword(parts[1])))
            return "OK registered";
        return "ERROR registration failed";
    }

    // LOGIN login password
    if (cmd == "LOGIN") {
        if (parts.size() < 2) return "ERROR need: LOGIN login password";
        if (DataBase::getInstance()->authUser(parts[0], hashPassword(parts[1]))) {
            DataBase::getInstance()->updateSocketID(parts[0], socketID);
            return "OK logged in";
        }
        return "ERROR wrong login or password";
    }

    // STATS login
    if (cmd == "STATS") {
        if (parts.size() < 1) return "ERROR need: STATS login";
        return DataBase::getInstance()->getStatsByLogin(parts[0]);
    }

    // LOGOUT
    if (cmd == "LOGOUT") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        DataBase::getInstance()->logoutUser(login);
        return "OK logged out";
    }

    // Шаг интегрирования h = (b - a) / n
    // Формат: CALC_H a b n
    if (cmd == "CALC_H") {
        if (parts.size() < 3) return "ERROR need: CALC_H a b n";
        double a = parts[0].toDouble();
        double b = parts[1].toDouble();
        int n = parts[2].toInt();
        if (n <= 0) return "ERROR n must be > 0";
        double h = (b - a) / n;
        return "OK h=" + QString::number(h);
    }

    // Заглушки для заданий коллег
    if (cmd == "TASK1") return "TASK1 not implemented yet";
    if (cmd == "TASK2") return "TASK2 not implemented yet";
    if (cmd == "TASK3") return "TASK3 not implemented yet";
    if (cmd == "TASK4") return "TASK4 not implemented yet";

    return "ERROR unknown command";
}
