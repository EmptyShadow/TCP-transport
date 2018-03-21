//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_CLIENT_H
#define TCP_TRANSPORT_CLIENT_H

#include <vector>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "../tcpsocket/TCPSocket.h"
#include "../tcpsocket/Address.h"

#define PORT 9999
#define SERVERADDR_A 127
#define SERVERADDR_B 0
#define SERVERADDR_C 0
#define SERVERADDR_D 1

char *VectorStringsToCharArray(std::vector<std::string> &vector, int indexStart = 0, int indexEnd = -1);

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
    transactions.push_back("qwe|rty|6");
    transactions.push_back("qwe|rty|7");
    transactions.push_back("qwe|rty|8");
    transactions.push_back("qwe|rty|9");
    transactions.push_back("qwe|rty|10");

    char *res = nullptr;
    res = VectorStringsToCharArray(transactions, 0, 5);
    printf("%s %d\n", res, strlen(res));

    clientSocket.Send(serverAddress, res, strlen(res));
    delete res;

    res = nullptr;
    res = VectorStringsToCharArray(transactions, 5, 10);
    printf("%s %d\n", res, strlen(res));

    clientSocket.Send(serverAddress, res, strlen(res));
    delete res;

    printf("Exit...");
    return 0;
}

char *VectorStringsToCharArray(std::vector<std::string> &vector, int indexStart, int indexEnd) {
    if (indexEnd == -1) {
        indexEnd = vector.size();
    }
    int count = 0;
    char *resCharArray = nullptr;

    for (int i = indexStart; i < indexEnd; i++) {
        count += vector[i].length();

        resCharArray = (char *) realloc(resCharArray, count * sizeof(char));

        const char *str = vector[i].data();
        strcat(resCharArray, str);
    }

    return resCharArray;
}

#endif //TCP_TRANSPORT_CLIENT_H
