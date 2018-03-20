#include <iostream>
#include <thread>
#include "client.h"

int main() {
    std::thread th(client);
    th.join();

    return 0;
}