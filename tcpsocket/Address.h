//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_ADDRESS_H
#define TCP_TRANSPORT_ADDRESS_H

/**
 * Класс адресата, куда можно отсылать и принимать сообщения
 * Он хранит адресс и порт адресата
 */
class Address {
public:

    Address();

    /*Address(unsigned char a, unsigned short port);

    Address(unsigned int address, unsigned short port);

    unsigned int GetAddress() const;

    unsigned char GetA() const;

    unsigned short GetPort() const;

    bool operator==(const Address &other) const;

    bool operator!=(const Address &other) const;*/

private:

    unsigned int address;
    unsigned short port;
};


#endif //TCP_TRANSPORT_ADDRESS_H
