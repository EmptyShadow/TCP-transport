//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_UTILITIES_H
#define TCP_TRANSPORT_UTILITIES_H

#include <iostream>
#include <string>
#include <ctime>

namespace Util {
    // Получение текущей даты и времени YYYY-MM-DD.HH:mm:ss
    const std::string CurrentDateTime() {
        time_t now = time(NULL);
        struct tm tstruct;
        char buf[80];

        localtime_r(&now, &tstruct);

        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
}

#endif //TCP_TRANSPORT_UTILITIES_H
