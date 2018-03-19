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

bool TCPSocket::NonBlocking(char mode) {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int nonBlocking = mode;

    if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        if (mode == 1) {
            printf("failed to set non-blocking socket\n");
        } else {
            printf("failed to setvblocking socket\n");
        }
        return false;
    }
    return true;

#elif PLATFORM == PLATFORM_WINDOWS

    DWORD nonBlocking = mode;
    if ( ioctlsocket( handle, FIONBIO, &nonBlocking ) != 0 )
    {
        if (mode == 1) {
            printf("failed to set non-blocking socket\n");
        } else {
            printf("failed to setvblocking socket\n");
        }
        return false;
    }
    return true;

#endif
}

void TCPSocket::Close() {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    if (close(handle) != 0) {
        printf("failed to close socket");
    }
#elif PLATFORM == PLATFORM_WINDOWS
    if (closesocket(handle) != 0) {
        printf("failed to close socket");
    }
#endif
}