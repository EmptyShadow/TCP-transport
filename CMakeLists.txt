cmake_minimum_required(VERSION 3.9)
project(TCP_transport)

set(CMAKE_CXX_STANDARD 11)

add_executable(TCP_transport
        main.cpp
        tcpsocket/TCPSocket.cpp tcpsocket/TCPSocket.h
        platformdet.h
        tcpsocket/link_platform_h_socket.h
        tcpsocket/Address.cpp tcpsocket/Address.h
        Logger/Logger.cpp Logger/Logger.h
        Logger/Utilities.h)
target_link_libraries(TCP_transport pthread)