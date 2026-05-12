/**
 * \file windowmanager.h
 * \brief Объявление класса WindowManager — менеджера навигации между экранами.
 */
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QPointer>

class AuthWidget;
class RegisterWidget;
class MainMenuWidget;
class TaskWidget;
class StatsWidget;

/**
 * \class WindowManager
 * \brief Управляет отображением и переключением между виджетами приложения.
 *
 * Создаёт виджеты (AuthWidget, RegisterWidget, MainMenuWidget, TaskWidget, StatsWidget)
 * при первом обращении, связывает их сигналы с бизнес-логикой и управляет
 * видимостью экранов. Сетевые запросы делегирует SingletonClient.
 */
class WindowManager : public QObject
{
    Q_OBJECT
public:
    /**
     * \brief Создаёт менеджер и инициализирует TCP-клиент.
     * \param parent Родительский объект Qt.
     */
    explicit WindowManager(QObject *parent = nullptr);

    /**
     * \brief Показывает экран авторизации (стартовый экран приложения).
     *
     * Скрывает все остальные виджеты, очищает поля ввода.
     */
    void showAuth();

private:
    /**
     * \brief Выполняет авторизацию на сервере.
     * \param login    Логин пользователя.
     * \param password Пароль в открытом виде (будет хэширован).
     * \param errorMsg Сообщение об ошибке (заполняется при неудаче).
     * \return true если авторизация прошла успешно.
     */
    bool doLogin(const QString &login, const QString &password, QString &errorMsg);

    /**
     * \brief Выполняет регистрацию нового пользователя на сервере.
     * \param login    Желаемый логин.
     * \param password Пароль в открытом виде (будет хэширован).
     * \param errorMsg Сообщение об ошибке (заполняется при неудаче).
     * \return true если регистрация прошла успешно.
     */
    bool doRegister(const QString &login, const QString &password, QString &errorMsg);

    /**
     * \brief Выполняет выход из системы на сервере.
     * \param errorMsg Сообщение об ошибке (заполняется при неудаче).
     * \return true если выход прошёл успешно.
     */
    bool doLogout(QString &errorMsg);

    /**
     * \brief Запрашивает статистику пользователя с сервера.
     * \param login Логин пользователя.
     * \param t1    Счётчик задания 1 (выходной параметр).
     * \param t2    Счётчик задания 2 (выходной параметр).
     * \param t3    Счётчик задания 3 (выходной параметр).
     * \param t4    Счётчик задания 4 (выходной параметр).
     * \return true если статистика успешно получена.
     */
    bool doStats(const QString &login, int &t1, int &t2, int &t3, int &t4);

    /**
     * \brief Запрашивает у сервера текст задания.
     * \param taskNum Номер задания (1–4).
     * \return Текст задания для отображения пользователю.
     */
    QString doGetTask(int taskNum);

    /**
     * \brief Отправляет ответ пользователя на сервер для проверки.
     * \param taskNum Номер задания (1–4).
     * \param answer  Ответ пользователя.
     * \return "CORRECT", "INCORRECT" или строка ошибки.
     */
    QString doSendAnswer(int taskNum, const QString &answer);

    /**
     * \brief Вычисляет SHA-256 хэш пароля.
     * \param password Пароль в открытом виде.
     * \return Hex-строка SHA-256.
     */
    static QString hashPassword(const QString &password);

    /**
     * \brief Извлекает текст ошибки из ответа сервера вида "ERROR ...".
     * \param response Ответ сервера.
     * \return Текст после "ERROR ", или исходная строка если префикс не найден.
     */
    static QString extractError(const QString &response);

    /**
     * \brief Показывает главное меню.
     *
     * Скрывает все остальные виджеты и отображает имя текущего пользователя.
     */
    void showMenu();

    /**
     * \brief Создаёт TaskWidget и подключает его сигналы к логике проверки ответа.
     */
    void createTaskWidget();

    QString m_currentLogin;    ///< Логин текущего авторизованного пользователя.
    int     m_currentTask = 0; ///< Номер задания, открытого в данный момент.

    QPointer<AuthWidget>      m_authWidget;     ///< Экран авторизации.
    QPointer<RegisterWidget>  m_registerWidget; ///< Экран регистрации.
    QPointer<MainMenuWidget>  m_mainMenu;       ///< Главное меню.
    QPointer<TaskWidget>      m_taskWidget;     ///< Экран задания.
    QPointer<StatsWidget>     m_statsWidget;    ///< Экран статистики.
};

#endif
