#include <iostream>
#include <thread>
#include "server.h"

int main() {
    std::thread th(server);
    th.join();

    return 0;
}