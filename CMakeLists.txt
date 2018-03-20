cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 11)

project(TCP_tests)

add_executable(TCP_tests
        main.cpp
        tcpsocket/TCPSocket.cpp tcpsocket/TCPSocket.h
        platformdet.h
        tcpsocket/link_platform_h_socket.h
        tcpsocket/Address.cpp tcpsocket/Address.h
        Logger/Logger.cpp Logger/Logger.h
        Logger/Utilities.h)
target_link_libraries(TCP_tests pthread)

project(TCP_server)
add_executable(TCP_server
        tcpserver/main.cpp
        tcpserver/server.h
        tcpsocket/TCPSocket.cpp tcpsocket/TCPSocket.h
        platformdet.h
        tcpsocket/link_platform_h_socket.h
        tcpsocket/Address.cpp tcpsocket/Address.h
        Logger/Logger.cpp Logger/Logger.h
        Logger/Utilities.h)
target_link_libraries(TCP_server pthread)

project(TCP_client)
add_executable(TCP_client
        tcpclient/main.cpp
        tcpclient/client.h
        tcpsocket/TCPSocket.cpp tcpsocket/TCPSocket.h
        platformdet.h
        tcpsocket/link_platform_h_socket.h
        tcpsocket/Address.cpp tcpsocket/Address.h
        Logger/Logger.cpp Logger/Logger.h
        Logger/Utilities.h
        )
target_link_libraries(TCP_client pthread)