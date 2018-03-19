//
// Created by emptyshadow on 20.03.18.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
    // Для Winsock требуется вызов функции, которая инициализирует winsock
    #if PLATFORM == PLATFORM_WINDOWS
        WSADATA WsaData;
        if (WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR) {
            printf("WSAStartup failed!!\n");
            this.handle = -1;
        }
    #endif

    // создание сокета
    int handle = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if ( handle <= 0 )
    {
        printf( "failed to create socket\n" );
    }
}

TCPSocket::~TCPSocket() {
    #if PLATFORM == PLATFORM_WINDOWS
        WSACleanup();
    #endif
}