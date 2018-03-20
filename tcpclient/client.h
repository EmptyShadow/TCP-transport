//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_CLIENT_H
#define TCP_TRANSPORT_CLIENT_H

#include <vector>
#include "stdio.h"
#include "../tcpsocket/TCPSocket.h"
#include "../tcpsocket/Address.h"

#define PORT 9999
#define SERVERADDR_A 127
#define SERVERADDR_B 0
#define SERVERADDR_C 0
#define SERVERADDR_D 1

int client() {
    printf("TCP client\n");

    // Создаем потоковый сокет
    TCPSocket clientSocket;

    // Перевод в неблокирующий режим
    //clientSocket.NonBlocking();

    Address serverAddress(SERVERADDR_A,
                          SERVERADDR_B,
                          SERVERADDR_C,
                          SERVERADDR_D,
                          PORT);

    // Подключение к серверу
    if (!clientSocket.Connect(serverAddress)) {
        printf("Connection error\n");
        return -1;
    }

    printf("Connection with %d.%d.%d.%d:%d successfully installed\n",
           SERVERADDR_A,
           SERVERADDR_B,
           SERVERADDR_C,
           SERVERADDR_D,
           PORT);

    std::vector<std::string> transactions;
    transactions.push_back("qwe|rty|1");
    transactions.push_back("qwe|rty|2");
    transactions.push_back("qwe|rty|3");
    transactions.push_back("qwe|rty|4");
    transactions.push_back("qwe|rty|5");

    printf("%s", transactions.data()->data());

    clientSocket.Send(serverAddress, transactions.data(), sizeof(transactions.data()));

    printf("Exit...");
    return 0;
}

#endif //TCP_TRANSPORT_CLIENT_H
