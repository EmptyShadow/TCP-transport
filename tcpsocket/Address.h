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

    Address(unsigned char a, unsigned char b,
            unsigned char c, unsigned char d,
            unsigned short port);

    Address(unsigned int address, unsigned short port);

    unsigned int GetAddress() const;

    unsigned char GetA() const;

    unsigned char GetB() const;

    unsigned char GetC() const;

    unsigned char GetD() const;

    unsigned short GetPort() const;

    /**
     * Получение по объекту структуры адресации сокета
     * @return
     */
    sockaddr_in GetAddressToSockAddrIn() const;

    /**
     * Получение порта в формате следования байтов big-endian
     * @return
     */
    unsigned short GetPortToHtons() const;

    /**
     * Изменить информацию об адрисе
     * @param sockaddrIn структура адреса сокета
     */
    void SetAddressInfo(const sockaddr_in &sockaddrIn);

    bool operator==(const Address &other) const;

    bool operator!=(const Address &other) const;

private:

    unsigned int address;
    unsigned short port;
};


#endif //TCP_TRANSPORT_ADDRESS_H
