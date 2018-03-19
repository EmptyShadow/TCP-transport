//
// Created by emptyshadow on 20.03.18.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
    // Для Winsock требуется вызов функции, которая инициализирует winsock
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    if (WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR) {
        printf("WSAStartup failed\n");
        this.handle = -1;
    }
#endif

    // создание сокета
    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (handle <= 0) {
        printf("failed to create socket\n");
    }
}

TCPSocket::~TCPSocket() {
#if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
#endif
}

bool TCPSocket::Open(unsigned short port) {
    // структура для указания конечной точки,
    // к которой будет осуществленно подключение
    sockaddr_in address;
    // семейство адресов
    address.sin_family = AF_INET;
    // ip - адрес = все адреса локального хоста
    address.sin_addr.s_addr = INADDR_ANY;
    // ip - порт, к которому привязывается сокет
    address.sin_port = htons((unsigned short) port);


    if (bind(handle, (const sockaddr *) &address, sizeof(sockaddr_in)) < 0) {
        printf("faildes to bind socket\n");
        return false;
    }
    return true;
}