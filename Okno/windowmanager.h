#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QPointer>

class AuthWidget;
class RegisterWidget;
class MainMenuWidget;
class TaskWidget;
class StatsWidget;

class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    void showAuth();

private:
    bool    doLogin   (const QString &login, const QString &password, QString &errorMsg);
    bool    doRegister(const QString &login, const QString &password, QString &errorMsg);
    bool    doLogout  (QString &errorMsg);
    bool    doStats   (const QString &login, int &t1, int &t2, int &t3, int &t4);

    QString doGetTask(int taskNum);
    QString doSendAnswer(int taskNum, const QString &answer);

    static QString hashPassword(const QString &password);
    static QString extractError(const QString &response);

    void showMenu();
    void createTaskWidget();

    QString m_currentLogin;
    int     m_currentTask = 0;

    QPointer<AuthWidget>      m_authWidget;
    QPointer<RegisterWidget>  m_registerWidget;
    QPointer<MainMenuWidget>  m_mainMenu;
    QPointer<TaskWidget>      m_taskWidget;
    QPointer<StatsWidget>     m_statsWidget;
};

#endif
