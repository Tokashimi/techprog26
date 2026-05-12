/**
 * \file database.h
 * \brief Объявление класса DataBase — singleton-обёртки над SQLite.
 */
#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * \class DataBase
 * \brief Singleton-класс для работы с базой данных SQLite.
 *
 * Хранит данные пользователей в таблице Person:
 * login, password (SHA-256 hex), socketID текущей сессии,
 * параметры активного задания и счётчики задач 1–4.
 *
 * Доступ к единственному экземпляру — через DataBase::getInstance().
 */
class DataBase
{
private:
    static DataBase* p_instance; ///< Единственный экземпляр (Singleton).
    QSqlDatabase db;             ///< Объект соединения с базой данных.

    DataBase() {}
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;

    ~DataBase() {
        if (db.isOpen())
            db.close();
    }

public:
    /**
     * \brief Возвращает единственный экземпляр DataBase.
     * \return Указатель на экземпляр DataBase.
     */
    static DataBase* getInstance();

    /**
     * \brief Инициализирует соединение с БД и создаёт таблицу Person.
     *
     * При запуске сбрасывает все socketID в NULL (завершает старые сессии).
     * \param dbPath Путь к файлу SQLite (по умолчанию "timp.db").
     * \return true если БД успешно открыта и таблица создана.
     */
    bool init(const QString& dbPath = "timp.db");

    // ── Управление пользователями ──────────────────────────────────────────────

    /**
     * \brief Регистрирует нового пользователя.
     * \param login    Логин (уникальный PRIMARY KEY).
     * \param password Хэш пароля (SHA-256 hex).
     * \return true если запись успешно добавлена.
     */
    bool registerUser(const QString& login, const QString& password);

    /**
     * \brief Проверяет логин и пароль пользователя.
     * \param login    Логин пользователя.
     * \param password Хэш пароля (SHA-256 hex).
     * \return true если пара логин/пароль найдена в БД.
     */
    bool authUser(const QString& login, const QString& password);

    /**
     * \brief Проверяет, занят ли логин.
     * \param login Логин для проверки.
     * \return true если логин уже существует.
     */
    bool loginExists(const QString& login);

    // ── Управление сессиями ────────────────────────────────────────────────────

    /**
     * \brief Привязывает дескриптор сокета к логину (вход в систему).
     * \param login    Логин пользователя.
     * \param socketID Строковое представление дескриптора сокета.
     * \return true если обновление прошло успешно.
     */
    bool updateSocketID(const QString& login, const QString& socketID);

    /**
     * \brief Возвращает логин пользователя по дескриптору его сокета.
     * \param socketID Дескриптор сокета.
     * \return Логин, или пустую строку если сокет не авторизован.
     */
    QString getLoginBySocket(const QString& socketID);

    /**
     * \brief Сбрасывает socketID пользователя (выход из системы).
     * \param login Логин пользователя.
     * \return true если обновление прошло успешно.
     */
    bool logoutUser(const QString& login);

    // ── Статистика ─────────────────────────────────────────────────────────────

    /**
     * \brief Возвращает статистику пользователя в виде строки.
     *
     * Формат ответа: "STATS login: task1=N task2=N task3=N task4=N".
     * \param login Логин пользователя.
     * \return Строка статистики, или "ERROR user not found".
     */
    QString getStatsByLogin(const QString& login);

    /**
     * \brief Обновляет счётчик задания для пользователя.
     *
     * Инкрементирует счётчик при правильном ответе, декрементирует при неверном.
     * \param login Логин пользователя.
     * \param task  Номер задания (1–4).
     * \param res   true — правильный ответ, false — неправильный.
     */
    void updateStats(const QString& login, int task, bool res);

    // ── Параметры задания ──────────────────────────────────────────────────────

    /**
     * \brief Сохраняет параметры активного задания для пользователя.
     * \param login  Логин пользователя.
     * \param params Строка параметров задания.
     * \return true если сохранение прошло успешно.
     */
    bool saveTaskParams(const QString& login, const QString& params);

    /**
     * \brief Возвращает сохранённые параметры активного задания.
     * \param login Логин пользователя.
     * \return Строка параметров, или пустую строку если задания нет.
     */
    QString getTaskParams(const QString& login);
};

#endif
