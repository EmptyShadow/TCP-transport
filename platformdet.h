//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_PLATFORMDET_H
#define TCP_TRANSPORT_PLATFORMDET_H

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
    #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM PLATFORM_MAC
#else
    #define PLATFORM PLATFORM_UNIX
#endif

#endif //TCP_TRANSPORT_PLATFORMDET_H
