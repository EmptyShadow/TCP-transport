//
// Created by emptyshadow on 20.03.18.
//

#include <vector>
#include <thread>
#include <sstream>
#include "mutex"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../tcpsocket/TCPSocket.h"

#define PORT 9999

#define PRINT_N_USERS if (countActiveUsers) \
printf("%d user on-line\n", countActiveUsers);\
else printf("No User on-line\n");

int ServeTheUser(TCPSocket *serveSocket, Address *userAddress);
int Transfer(const char* data);

static int countActiveUsers = 0;
std::mutex mutexServe;

int server() {
    printf("TCP server\n");
    // Создаем потоковый сокет
    TCPSocket serverSocket;

    // Перевод в неблокирующий режим
    // serverSocket.NonBlocking();

    // привязываем его к локальному хосту и порту
    if (!serverSocket.Open(PORT)) {
        printf("Error bind\n");
        return -1;
    }

    // Слушаем порт и ждем подключений пользователей
    if (!serverSocket.Listen(0x100)) {
        printf("Error listen port: %d\n", PORT);
        return -1;
    }

    printf("Waiting for connections\n");

    // Извлечение сообщений из очереди
    TCPSocket *serveSocket; // сокет для обслуживанияпользователя
    Address userAddress; // адрес пользователя
    while ((serveSocket = serverSocket.Accept(userAddress)) != nullptr) {
        countActiveUsers++;

        // вывод информации о пользователе
        printf("%d.%d.%d.%d:%d new connect!\n",
               userAddress.GetA(),
               userAddress.GetB(),
               userAddress.GetC(),
               userAddress.GetB(),
               userAddress.GetPort()
        );
        PRINT_N_USERS

        // создание нового потока для обслуживания
        std::thread newServeTh(ServeTheUser,
                               serveSocket,
                               new Address(
                                       userAddress.GetAddress(),
                                       userAddress.GetPort()
                               )
        );
        newServeTh.join();
    }

    return 0;
}

int ServeTheUser(TCPSocket *serveSocket, Address *userAddress) {

    printf("Serve user %d.%d.%d.%d:%d\n",
           userAddress->GetA(),
           userAddress->GetB(),
           userAddress->GetC(),
           userAddress->GetB(),
           userAddress->GetPort()
    );

    vector<string> transactions(5);

    // все данные от пользователя
    char *data = nullptr;
    // количество байт всего переданно
    int countData = 0;
    // количество прочтенных данных
    int bytes_recv;
    // буфер куда читают
    char buff[1024];
    // читаем все пока есть соединение
    while ((bytes_recv = serveSocket->Receive(buff, 1024)) > 0) {
        countData += bytes_recv;
        data = (char *) realloc(data, countData * sizeof(char));
        strcat(data, buff);
    }

    // Передача принятых данных
    Transfer(data);
    delete data;

    mutexServe.lock();
    countActiveUsers--;
    mutexServe.unlock();

    delete serveSocket;
    delete userAddress;
    return 0;
}

int Transfer(const char* data) {
    printf("Transfer data\n");

    string str(data);
    stringstream ss(str);
    string token;

    printf("full data: \"%s\"\n", str.c_str());
    while (getline(ss, token, '|')) {
        printf("%s\n", token.c_str());
    }
    return 0;
}

