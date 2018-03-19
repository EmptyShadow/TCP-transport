//
// Created by emptyshadow on 20.03.18.
//

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