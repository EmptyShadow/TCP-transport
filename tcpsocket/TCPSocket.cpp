//
// Created by emptyshadow on 20.03.18.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
    // Для Winsock требуется вызов функции, которая инициализирует winsock
#if PLATFORM == PLATFORM_WINDOWS

    WSADATA WsaData;
    if (WSAStartup( MAKEWORD(2,2), &WsaData ) == NO_ERROR) {
        LOGGER->Log("WSAStartup failed");
        this.handle = -1;
    }

#endif

    // создание сокета
    handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (handle <= 0) {
        LOGGER->Log("failed to create socket");
    }
}

TCPSocket::TCPSocket(int handle) {
    this->handle = handle;
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
        LOGGER->Log("faildes to bind socket port:%d", port);
        return false;
    }

    return true;
}

bool TCPSocket::NonBlocking(char mode) {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int nonBlocking = mode;

    if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1) {
        if (mode == 1) {
            LOGGER->Log("failed to set non-blocking socket");
        } else {
            LOGGER->Log("failed to setvblocking socket");
        }
        return false;
    }
    return true;

#elif PLATFORM == PLATFORM_WINDOWS

    DWORD nonBlocking = mode;
    if ( ioctlsocket( handle, FIONBIO, &nonBlocking ) != 0 )
    {
        if (mode == 1) {
            LOGGER->Log("failed to set non-blocking socket");
        } else {
            LOGGER->Log("failed to setvblocking socket");
        }
        return false;
    }
    return true;

#endif
}

void TCPSocket::Close() {
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    if (close(handle) != 0) {
        LOGGER->Log("failed to close socket");
    }
#elif PLATFORM == PLATFORM_WINDOWS
    if (closesocket(handle) != 0) {
        LOGGER->Log("failed to close socket");
    }
#endif
}

bool TCPSocket::Send(const Address &destination, const void *packet_data, int packet_size) {
    sockaddr_in address = destination.GetAddressToSockAddrIn();

    int sent_bytes = sendto(handle, (const char *) packet_data, packet_size,
                            0, (sockaddr *) &address, sizeof(sockaddr_in));

    if (sent_bytes != packet_size) {
        LOGGER->Log("failed to send packet: return value = %d\n", sent_bytes);
        return false;
    }

    return true;
}

int TCPSocket::ReceiveFrom(Address &sender, void *data, int size) {
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int received_bytes = recvfrom(handle, (char *) data, size,
                                  0, (sockaddr *) &from, &fromLength);

    if (received_bytes < 0) {
        LOGGER->Log("failed received bytes");
    } else {
        sender.SetAddressInfo(from);
    }

    return received_bytes;
}

int TCPSocket::Receive(void *data, int size) {
    int received_bytes = recv(handle, data, size, 0);

    if (received_bytes < 0) {
        LOGGER->Log("failed received bytes");
    }

    return received_bytes;
}

bool TCPSocket::Listen(unsigned int max_count_package_in_queue) {
    int res = listen(handle, max_count_package_in_queue);
    if (res != 0) {
        LOGGER->Log("failed listen port");
        return false;
    }
    return true;
}

TCPSocket *TCPSocket::Accept(Address &address) {
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int newHandle = accept(handle, (sockaddr *) &from, &fromLength);

    if (newHandle < 0) {
        LOGGER->Log("failed accept socket");
        return nullptr;
    }

    address.SetAddressInfo(from);
    return new TCPSocket(newHandle);
}

bool TCPSocket::Connect(const Address &address) {
    sockaddr_in from = address.GetAddressToSockAddrIn();
    socklen_t fromLength = sizeof(from);

    int res = connect(handle, (sockaddr *) &from, fromLength);

    if (res != 0) {
        LOGGER->Log("failed connect");
        return false;
    }

    return true;
}