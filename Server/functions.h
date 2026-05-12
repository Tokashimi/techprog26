/**
 * \file functions.h
 * \brief Объявление функции parsing() — маршрутизатора команд сервера.
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QStringList>
#include <QDebug>
#include <QVector>

/**
 * \brief Разбирает команду клиента и возвращает строку-ответ.
 *
 * Поддерживаемые команды:
 * - \c LOGIN \c login \c password — авторизация пользователя.
 * - \c REGISTER \c login \c password — регистрация нового пользователя.
 * - \c LOGOUT — завершение сессии текущего пользователя.
 * - \c STATS \c login — запрос статистики пользователя.
 * - \c TASK1 .. \c TASK4 — генерация и выдача задания.
 * - \c ANSWER \c value — проверка ответа на активное задание.
 *
 * \param str      Полная строка запроса от клиента.
 * \param socketID Строковый идентификатор сокета отправителя.
 * \return Строка ответа сервера (например, "OK logged in" или "ERROR ...").
 */
QString parsing(const QString& str, const QString& socketID);

#endif
