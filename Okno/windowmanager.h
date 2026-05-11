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
    // Вспомогательные методы: отправка команд и парсинг ответов
    bool    doLogin   (const QString &login, const QString &password, QString &errorMsg);
    bool    doRegister(const QString &login, const QString &password, QString &errorMsg);
    bool    doLogout  (QString &errorMsg);
    bool    doStats   (const QString &login, int &t1, int &t2, int &t3, int &t4);

    static QString hashPassword(const QString &password);
    static QString extractError(const QString &response);

    void showMenu ();
    void createTaskWidget();

    QString m_currentLogin;

    QPointer<AuthWidget>      m_authWidget;
    QPointer<RegisterWidget>  m_registerWidget;
    QPointer<MainMenuWidget>  m_mainMenu;
    QPointer<TaskWidget>      m_taskWidget;
    QPointer<StatsWidget>     m_statsWidget;
};

#endif // WINDOWMANAGER_H
