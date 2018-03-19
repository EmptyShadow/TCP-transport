#include <iostream>
#include "tcpsocket/TCPSocket.h"

int main() {
    TCPSocket socket;
    bool res = socket.Open();
    std::cout << res << std::endl;
    res = socket.NonBlocking();
    std::cout << res << std::endl;
    return 0;
}