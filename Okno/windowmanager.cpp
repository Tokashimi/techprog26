#include "windowmanager.h"
#include "singletonclient.h"
#include "authwidget.h"
#include "registerwidget.h"
#include "mainmenuwidget.h"
#include "taskwidget.h"
#include "statswidget.h"

#include <QCryptographicHash>
#include <QMessageBox>

QString WindowManager::hashPassword(const QString &password)
{
    return QCryptographicHash::hash(
               password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

QString WindowManager::extractError(const QString &response)
{
    if (response.startsWith("ERROR "))
        return response.mid(6).trimmed();
    return response;
}

WindowManager::WindowManager(QObject *parent)
    : QObject(parent)
{
    SingletonClient::getInstance();
}

bool WindowManager::doLogin(const QString &login, const QString &password,
                             QString &errorMsg)
{
    QString cmd = QString("LOGIN %1 %2").arg(login, hashPassword(password));
    QString response = SingletonClient::getInstance()->send_msg_to_server(cmd);
    if (response == "OK logged in") {
        m_currentLogin = login;
        return true;
    }
    errorMsg = extractError(response);
    if (errorMsg.isEmpty()) errorMsg = "Неверный логин или пароль";
    return false;
}

bool WindowManager::doRegister(const QString &login, const QString &password,
                                QString &errorMsg)
{
    QString cmd = QString("REGISTER %1 %2").arg(login, hashPassword(password));
    QString response = SingletonClient::getInstance()->send_msg_to_server(cmd);
    if (response == "OK registered")
        return true;
    errorMsg = extractError(response);
    if (errorMsg.isEmpty()) errorMsg = "Ошибка регистрации";
    return false;
}

bool WindowManager::doLogout(QString &errorMsg)
{
    QString response = SingletonClient::getInstance()->send_msg_to_server("LOGOUT");
    if (response == "OK logged out")
        return true;
    errorMsg = extractError(response);
    if (errorMsg.isEmpty()) errorMsg = "Ошибка выхода";
    return false;
}

bool WindowManager::doStats(const QString &login,
                             int &t1, int &t2, int &t3, int &t4)
{
    QString cmd = QString("STATS %1").arg(login);
    QString response = SingletonClient::getInstance()->send_msg_to_server(cmd);
    if (!response.startsWith("STATS "))
        return false;

    auto extractInt = [&](const QString &key) -> int {
        int idx = response.indexOf(key + "=");
        if (idx == -1) return 0;
        int start = idx + key.length() + 1;
        int end = response.indexOf(' ', start);
        QString val = (end == -1) ? response.mid(start)
                                  : response.mid(start, end - start);
        return val.toInt();
    };

    t1 = extractInt("task1");
    t2 = extractInt("task2");
    t3 = extractInt("task3");
    t4 = extractInt("task4");
    return true;
}

void WindowManager::showAuth()
{
    if (!m_authWidget) {
        m_authWidget = new AuthWidget;

        connect(m_authWidget, &AuthWidget::loginRequested,
                this, [this](const QString &login, const QString &password) {
                    QString err;
                    if (doLogin(login, password, err)) {
                        showMenu();
                    } else {
                        QMessageBox::warning(m_authWidget, "Авторизация", err);
                    }
                });

        connect(m_authWidget, &AuthWidget::switchToRegister, this, [this]() {
            if (!m_registerWidget) {
                m_registerWidget = new RegisterWidget;

                connect(m_registerWidget, &RegisterWidget::registerRequested,
                        this, [this](const QString &login, const QString &password) {
                            QString err;
                            if (doRegister(login, password, err)) {
                                QMessageBox::information(m_registerWidget,
                                    "Регистрация",
                                    "Регистрация прошла успешно!");
                                m_registerWidget->hide();
                                showAuth();
                            } else {
                                QMessageBox::warning(m_registerWidget,
                                    "Регистрация", err);
                            }
                        });

                connect(m_registerWidget, &RegisterWidget::switchToAuth,
                        this, [this]() {
                            m_registerWidget->hide();
                            showAuth();
                        });
            }
            m_authWidget->hide();
            m_registerWidget->show();
            m_registerWidget->raise();
            m_registerWidget->activateWindow();
        });
    }

    if (m_registerWidget) m_registerWidget->hide();
    if (m_mainMenu)       m_mainMenu->hide();
    if (m_taskWidget)     m_taskWidget->hide();
    if (m_statsWidget)    m_statsWidget->hide();

    m_authWidget->clearFields();
    m_authWidget->show();
    m_authWidget->raise();
    m_authWidget->activateWindow();
}

void WindowManager::showMenu()
{
    if (!m_mainMenu) {
        m_mainMenu = new MainMenuWidget;

        auto openTask = [this](const QString &text) {
            m_mainMenu->hide();
            if (!m_taskWidget) createTaskWidget();
            m_taskWidget->setTaskText(text);
            m_taskWidget->show();
            m_taskWidget->raise();
            m_taskWidget->activateWindow();
        };

        connect(m_mainMenu, &MainMenuWidget::task1Clicked, this, [this, openTask]() {
            openTask("Задание 1\n\nЗаглушечка");
        });
        connect(m_mainMenu, &MainMenuWidget::task2Clicked, this, [this, openTask]() {
            openTask("Задание 2\n\nЗаглушечка");
        });
        connect(m_mainMenu, &MainMenuWidget::task3Clicked, this, [this, openTask]() {
            openTask("Задание 3\n\nЗаглушечка");
        });
        connect(m_mainMenu, &MainMenuWidget::task4Clicked, this, [this, openTask]() {
            openTask("Задание 4\n\nЗаглушечка");
        });

        connect(m_mainMenu, &MainMenuWidget::statsClicked, this, [this]() {
            int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
            if (doStats(m_currentLogin, t1, t2, t3, t4)) {
                if (!m_statsWidget) {
                    m_statsWidget = new StatsWidget;
                    connect(m_statsWidget, &StatsWidget::backToMenuRequested,
                            this, [this]() {
                                m_statsWidget->hide();
                                showMenu();
                            });
                }
                m_mainMenu->hide();
                m_statsWidget->setStats(m_currentLogin, t1, t2, t3, t4);
                m_statsWidget->show();
                m_statsWidget->raise();
                m_statsWidget->activateWindow();
            } else {
                QMessageBox::warning(m_mainMenu, "Статистика",
                    "Не удалось получить статистику");
            }
        });

        connect(m_mainMenu, &MainMenuWidget::logoutClicked, this, [this]() {
            QString err;
            if (doLogout(err)) {
                m_currentLogin.clear();
                showAuth();
            } else {
                QMessageBox::warning(m_mainMenu, "Выход", err);
            }
        });
    }

    if (m_authWidget)  m_authWidget->hide();
    if (m_taskWidget)  m_taskWidget->hide();
    if (m_statsWidget) m_statsWidget->hide();

    m_mainMenu->setUsername(m_currentLogin);
    m_mainMenu->show();
    m_mainMenu->raise();
    m_mainMenu->activateWindow();
}

void WindowManager::createTaskWidget()
{
    m_taskWidget = new TaskWidget;

    connect(m_taskWidget, &TaskWidget::answerSubmitted,
            this, [this](const QString &answer) {
                QMessageBox::information(m_taskWidget, "Ответ",
                    QString("Ваш ответ: %1\n"
                            "(Проверка ответов будет добавлена позже)").arg(answer));
            });

    connect(m_taskWidget, &TaskWidget::backToMenuRequested,
            this, [this]() {
                m_taskWidget->hide();
                showMenu();
            });
}
