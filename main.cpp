#include <iostream>
#include <thread>
#include "tcpsocket/TCPSocket.h"
#include "tcpsocket/Address.h"
#include "Logger/Logger.h"
#include "tcpsocket/link_platform_h_socket.h"

void save(const std::string &url)
{
    LOGGER->Log(url);
}

int main() {

    Address address1(127, 0, 0, 1, 999);

    printf("%d\n", address1.GetAddressToSockAddrIn().sin_addr.s_addr);
    printf("%d\n", htonl(inet_addr("127.0.0.1")));

    /*TCPSocket socket;
    bool res = socket.Open();
    std::cout << res << std::endl;
    res = socket.NonBlocking();
    std::cout << res << std::endl;
    socket.Close();

    Address address1(192, 168, 45, 3, 8080);
    Address address2(195, 168, 45, 3, 8080);

    printf("%d\n", address1.GetAddress());
    printf("%d\n", address1.GetA());
    printf("%d\n", address1.GetB());
    printf("%d\n", address1.GetC());
    printf("%d\n", address1.GetD());
    printf("%d\n", address1.GetPort());

    printf("%d\n", address1 == address2);
    printf("%d\n", address1 != address2);


    std::thread t1(save, "t1");
    std::thread t2(save, "t2");
    std::thread t3(save, "t3");
    std::thread t4(save, "t4");
    std::thread t5(save, "t5");
    std::thread t6(save, "t6");
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();*/

    return 0;
}