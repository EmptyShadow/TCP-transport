#include <iostream>
#include "tcpsocket/TCPSocket.h"
#include "tcpsocket/Address.h"

int main() {
    /*TCPSocket socket;
    bool res = socket.Open();
    std::cout << res << std::endl;
    res = socket.NonBlocking();
    std::cout << res << std::endl;
    socket.Close();*/

    Address address(192, 168, 45, 3, 8080);

    printf("%d\n", address.GetAddress());
    printf("%d\n", address.GetA());
    printf("%d\n", address.GetB());
    printf("%d\n", address.GetC());
    printf("%d\n", address.GetD());
    printf("%d\n", address.GetPort());

    return 0;
}