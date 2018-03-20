//
// Created by emptyshadow on 20.03.18.
//

#include "Logger.h"
#include"Utilities.h"

const string Logger::m_sFileName = "log";
Logger* Logger::m_pThis = nullptr;
ofstream Logger::m_Logfile;

Logger::Logger() {

}

Logger *Logger::GetLogger() {
    // если логгер еще никто не использовал
    if (m_pThis == nullptr) {
        // то создаем логгер и создаем или открываем файл
        m_pThis = new Logger();
        m_Logfile.open(m_sFileName.c_str(), ios::out | ios::app);
    }
    return m_pThis;
}

void Logger::Close() {
    if (m_pThis != nullptr) {
        delete m_pThis;
        m_pThis = nullptr;
        m_Logfile.close();
    }
}

void Logger::Log(const char *format, ...) {
    char *sMessage = nullptr;
    int nLength = 0;

    va_list args;
    //  Получаем список аргументов
    va_start(args, format);

    // Подсчитываем количество символо в результирующем сообщении + '\n'
    nLength = vprintf(format, args) + 1;
    sMessage = new char[nLength];

    // записываем в сообщение строку форматирования, с вставленными в нее аргументами
    vsnprintf(sMessage, nLength, format, args);
    // выводим дату, время и сообщение
    loggerMutex.lock();
    m_Logfile << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    loggerMutex.unlock();

    va_end(args);

    // удаляем сообщение из памяти
    delete[] sMessage;
}

void Logger::Log(const string &sMessage) {
    loggerMutex.lock();
    m_Logfile << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    loggerMutex.unlock();
}

Logger &Logger::operator<<(const string &sMessage) {
    loggerMutex.lock();
    m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    loggerMutex.unlock();
    return *this;
}