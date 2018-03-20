//
// Created by emptyshadow on 20.03.18.
//

#include <netinet/in.h>
#include "Address.h"

Address::Address() {}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port) {
    address = (a << 24) | (b << 16) | (c << 8) | d;
    this->port = port;
}

Address::Address(unsigned int address, unsigned short port) {
    this->address = address;
    this->port = port;
}

unsigned int Address::GetAddress() const {
    return address;
}

unsigned char Address::GetA() const {
    return (unsigned char)(address >> 24);
}

unsigned char Address::GetB() const {
    return (unsigned char)(address >> 16);
}

unsigned char Address::GetC() const {
    return (unsigned char)(address >> 8);
}

unsigned char Address::GetD() const {
    return (unsigned char)(address);
}

unsigned short Address::GetPort() const {
    return port;
}

bool Address::operator==(const Address &other) const {
    return address == other.address && port == other.port;
}

bool Address::operator!=(const Address &other) const {
    return !(*this == other);
}

unsigned int Address::GetAddressToHtonl() const {
    return htonl(address);
}

unsigned short Address::GetPortToHtons() const {
    return htons(port);
}

sockaddr_in Address::GetAddressToSockAddrIn() const {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = GetAddressToHtonl();
    address.sin_port = GetPortToHtons();
    return address;
}

void Address::SetAddressInfo(const sockaddr_in &sockaddrIn) {
    address = ntohl(sockaddrIn.sin_addr.s_addr);
    port = ntohs(sockaddrIn.sin_port);
}