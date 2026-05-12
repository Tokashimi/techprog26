#include "functions.h"
#include "database.h"
#include <QCryptographicHash>
#include <QVector>
#include <algorithm>
#include <QRandomGenerator>

static QString hashPassword(const QString& password)
{
    return QCryptographicHash::hash(
               password.toUtf8(), QCryptographicHash::Sha256).toHex();
}


static QString generateTask1()
{
    int n = 4;
    QVector<QVector<int>> matrix(n, QVector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (QRandomGenerator::global()->bounded(2) == 1) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }
    QStringList result;
    result << QString::number(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result << QString::number(matrix[i][j]);
    int v = QRandomGenerator::global()->bounded(n);
    result << QString::number(v);
    return result.join(" ");
}

static bool checktask1(QStringList params)
{
    if (params.size() < 3) return false;
    int n = params[0].toInt();
    if (params.size() != n * n + 3) return false;

    int v = params[n * n + 1].toInt();
    QString userAnswer = params[n * n + 2];

    QVector<QVector<int>> matrix(n, QVector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = params[1 + i * n + j].toInt();

    QVector<bool> visited(n, false);
    QVector<int> component;
    QVector<int> stack;
    stack.append(v);
    while (!stack.isEmpty()) {
        int node = stack.last();
        stack.removeLast();
        if (visited[node]) continue;
        visited[node] = true;
        component.append(node);
        for (int i = 0; i < n; i++)
            if (matrix[node][i] != 0 && !visited[i])
                stack.append(i);
    }

    std::sort(component.begin(), component.end());
    QStringList answerParts = userAnswer.split(",");
    QVector<int> userComponent;
    for (const QString& s : answerParts)
        userComponent.append(s.trimmed().toInt());
    std::sort(userComponent.begin(), userComponent.end());
    return component == userComponent;
}


static QString generateTask2()
{
    int a = QRandomGenerator::global()->bounded(-5, 6);
    int b = a + QRandomGenerator::global()->bounded(1, 6);
    int n = QRandomGenerator::global()->bounded(2, 11);
    int funcIndex = QRandomGenerator::global()->bounded(5);
    return QString("%1 %2 %3 %4").arg(funcIndex).arg(a).arg(b).arg(n);
}

static bool checktask2(QStringList params)
{
    if (params.size() < 5) return false;
    double a = params[1].toDouble();
    double b = params[2].toDouble();
    int    n = params[3].toInt();
    double userAnswer = params[4].replace(",", ".").toDouble();
    double correctAnswer = (b - a) / n;
    return std::abs(userAnswer - correctAnswer) < 0.001;
}


static double evalFunc3(int funcId, double x, double y)
{
    switch (funcId) {
    case 0: return x + y;
    case 1: return x - y;
    case 2: return x * y;
    case 3: return x + 1;
    case 4: return y + 1;
    default: return x + y;
    }
}

static QString generateTask3()
{
    int funcId  = QRandomGenerator::global()->bounded(5);
    int x0      = QRandomGenerator::global()->bounded(-3, 4);
    int y0      = QRandomGenerator::global()->bounded(-3, 4);
    int h_tenth = QRandomGenerator::global()->bounded(1, 6);
    return QString("%1 %2 %3 %4").arg(funcId).arg(x0).arg(y0).arg(h_tenth);
}

static bool checktask3(QStringList params)
{
    if (params.size() < 5) return false;
    int    funcId     = params[0].toInt();
    double x0         = params[1].toDouble();
    double y0         = params[2].toDouble();
    double h          = params[3].toDouble() / 10.0;
    double userAnswer = params[4].replace(",", ".").toDouble();
    double correct    = y0 + h * evalFunc3(funcId, x0, y0);
    return std::abs(userAnswer - correct) < 0.01;
}


static double evalFunc4(int funcId, double x, double y)
{
    switch (funcId) {
    case 0: return x + y;
    case 1: return x - y;
    case 2: return x * y;
    case 3: return x + 1;
    case 4: return y + 1;
    default: return x + y;
    }
}

static QString generateTask4()
{
    int funcId  = QRandomGenerator::global()->bounded(5);
    int x0      = QRandomGenerator::global()->bounded(-3, 4);
    int y0      = QRandomGenerator::global()->bounded(-3, 4);
    int h_tenth = QRandomGenerator::global()->bounded(1, 6);
    return QString("%1 %2 %3 %4").arg(funcId).arg(x0).arg(y0).arg(h_tenth);
}

static bool checktask4(QStringList params)
{
    if (params.size() < 5) return false;
    int    funcId     = params[0].toInt();
    double x0         = params[1].toDouble();
    double y0         = params[2].toDouble();
    double h          = params[3].toDouble() / 10.0;
    double userAnswer = params[4].replace(",", ".").toDouble();
    double correct    = h * evalFunc4(funcId, x0, y0);
    return std::abs(userAnswer - correct) < 0.01;
}


static bool checkAnswer(int taskNum, const QString& savedParams, const QString& answer)
{
    QStringList params = savedParams.split(" ");
    params << answer;
    switch (taskNum) {
    case 1: return checktask1(params);
    case 2: return checktask2(params);
    case 3: return checktask3(params);
    case 4: return checktask4(params);
    default: return false;
    }
}


QString parsing(const QString& str, const QString& socketID)
{
    QStringList parts = str.trimmed().split(" ", Qt::SkipEmptyParts);
    if (parts.isEmpty()) return "ERROR unknown command";

    QString cmd = parts[0].toUpper();
    parts.removeFirst();

    qDebug() << "[Server] Команда:" << cmd << "| Параметры:" << parts;


    if (cmd == "REGISTER") {
        if (parts.size() < 2) return "ERROR need: REGISTER login password";
        if (DataBase::getInstance()->loginExists(parts[0]))
            return "ERROR login already taken";
        if (DataBase::getInstance()->registerUser(parts[0], hashPassword(parts[1])))
            return "OK registered";
        return "ERROR registration failed";
    }

    if (cmd == "LOGIN") {
        if (parts.size() < 2) return "ERROR need: LOGIN login password";
        if (DataBase::getInstance()->authUser(parts[0], hashPassword(parts[1]))) {
            DataBase::getInstance()->updateSocketID(parts[0], socketID);
            return "OK logged in";
        }
        return "ERROR wrong login or password";
    }

    if (cmd == "STATS") {
        if (parts.size() < 1) return "ERROR need: STATS login";
        return DataBase::getInstance()->getStatsByLogin(parts[0]);
    }

    if (cmd == "LOGOUT") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        DataBase::getInstance()->logoutUser(login);
        return "OK logged out";
    }


    if (cmd == "TASK1") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        QString params = generateTask1();
        DataBase::getInstance()->saveTaskParams(login, QString("1 ") + params);
        QStringList p = params.split(" ");
        int n = p[0].toInt();
        int v = p[p.size() - 1].toInt();
        QString output = QString("Вершина=%1 Матрица=").arg(v);
        for (int i = 0; i < n; i++) {
            output += "[";
            for (int j = 0; j < n; j++) {
                output += p[1 + i * n + j];
                if (j < n - 1) output += " ";
            }
            output += "]";
        }
        output += " Введите ответ через запятую (пример: 0,1,2)";
        return output;
    }

    if (cmd == "TASK2") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        QString params = generateTask2();
        DataBase::getInstance()->saveTaskParams(login, QString("2 ") + params);
        QStringList p = params.split(" ");
        QStringList functions = {"x^2", "x^3", "sin(x)", "cos(x)", "2x+1"};
        QString funcName = functions[p[0].toInt()];
        return QString("f(x)=%1 Отрезок=[%2,%3] Узлов=%4 | Найдите шаг h")
            .arg(funcName).arg(p[1]).arg(p[2]).arg(p[3]);
    }

    if (cmd == "TASK3") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        QString params = generateTask3();
        DataBase::getInstance()->saveTaskParams(login, QString("3 ") + params);
        QStringList p = params.split(" ");
        QStringList functions = {"x+y", "x-y", "x*y", "x+1", "y+1"};
        QString funcName = functions[p[0].toInt()];
        double h = p[3].toDouble() / 10.0;
        return QString("f(x,y)=%1 x0=%2 y0=%3 h=%4 | Найдите y1 методом Эйлера")
            .arg(funcName).arg(p[1]).arg(p[2]).arg(h, 0, 'f', 1);
    }

    if (cmd == "TASK4") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        QString params = generateTask4();
        DataBase::getInstance()->saveTaskParams(login, QString("4 ") + params);
        QStringList p = params.split(" ");
        QStringList functions = {"x+y", "x-y", "x*y", "x+1", "y+1"};
        QString funcName = functions[p[0].toInt()];
        double h = p[3].toDouble() / 10.0;
        return QString("f(x,y)=%1 x0=%2 y0=%3 h=%4 | Найдите k1 методом Рунге-Кутты")
            .arg(funcName).arg(p[1]).arg(p[2]).arg(h, 0, 'f', 1);
    }

    if (cmd == "ANSWER") {
        QString login = DataBase::getInstance()->getLoginBySocket(socketID);
        if (login.isEmpty()) return "ERROR not logged in";
        if (parts.isEmpty()) return "ERROR введите ответ";

        QString savedParams = DataBase::getInstance()->getTaskParams(login);
        if (savedParams.isEmpty()) return "ERROR сначала запросите задание";

        QStringList sp = savedParams.split(" ");
        int taskNum = sp[0].toInt();
        sp.removeFirst();
        QString taskParams = sp.join(" ");

        if (checkAnswer(taskNum, taskParams, parts[0])) {
            DataBase::getInstance()->updateStats(socketID, taskNum, true);
            DataBase::getInstance()->saveTaskParams(login, "");
            return "CORRECT";
        } else {
            DataBase::getInstance()->updateStats(socketID, taskNum, false);
            DataBase::getInstance()->saveTaskParams(login, "");
            return "INCORRECT";
        }
    }

    return "ERROR unknown command";
}
