//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_LINK_PLATFORM_H_SOCKET_H
#define TCP_TRANSPORT_LINK_PLATFORM_H_SOCKET_H

#include "../platformdet.h"

#if PLATFORM == PLATFORM_WINDOWS

    #pragma comment( lib, "wsock32.lib" )
    #include <winsock2.h>

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>

#endif

#endif //TCP_TRANSPORT_LINK_PLATFORM_H_SOCKET_H
