//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_LOGGER_H
#define TCP_TRANSPORT_LOGGER_H


#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>

using namespace std;
#define LOGGER Logger::GetLogger()

/**
*   Singleton Logger Class.
*/
class Logger {
public:
    /**
    *   Логирование сообщения
    *   @param Сообщение, которое должно быть залогированно
    */
    void Log(const std::string &sMessage);

    /**
    *   Форматированный вывод множества переменных
    *   @param строка форматирования выводимых переменных
    */
    void Log(const char *format, ...);

    /**
    *   Перегруженный оператор для записи сообщения
    *   @param сообщение для записи
    */
    Logger &operator<<(const string &sMessage);

    /**
    *   Функция получающая Logger
    *   @return синглтон объект Logger
    */
    static Logger *GetLogger();

private:
    Logger();

    Logger(const Logger &) {};             // copy constructor is private

    Logger &operator=(const Logger &) { return *this; };  // assignment operator is private

    /**
    *   Имя лог файла
    **/
    static const std::string m_sFileName;

    /**
    *   Синглетон указатель на объект логирования
    **/

    static Logger *m_pThis;
    /**
    *   Поток чтения и записи для лог файла
    **/
    static ofstream m_Logfile;
};

#endif //TCP_TRANSPORT_LOGGER_H
