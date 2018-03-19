//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_TCPSOCKET_H
#define TCP_TRANSPORT_TCPSOCKET_H

#include "stdio.h"
#include "link_platform_h_socket.h"

/**
 * Класс потокового сокета, который опирается на TCP
 */
class TCPSocket {
public:

    TCPSocket();

    ~TCPSocket();

    /**
     *  Привязка сокета к конкретному порту
     * @param port - порт, по умолчанию 0, система
     * сама выделит порт
     * @return
     */
    bool Open(unsigned short port = 0);

    /**
     * Перевод сокета в неблокирующий режим
     * @param mode - 1 - неблокирующий
     * 0 - блокирующий
     * @return
     */
    bool NonBlocking(char mode = 1);

//    /**
//     *
//     */
//    void Close();
//
//    /**
//     *
//     * @return
//     */
//    bool IsOpen() const;
//
//    /**
//     *
//     * @param destination
//     * @param data
//     * @param size
//     * @return
//     */
//    bool Send(const Address &destination, const void *data, int size);
//
//    /**
//     *
//     * @param sender
//     * @param data
//     * @param size
//     * @return
//     */
//    int Receive(Address &sender, void *data, int size);

private:

    /*
     * Дискриптор сокета
     */
    int handle;
};


#endif //TCP_TRANSPORT_TCPSOCKET_H
