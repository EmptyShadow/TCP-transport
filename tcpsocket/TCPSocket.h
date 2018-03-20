//
// Created by emptyshadow on 20.03.18.
//

#ifndef TCP_TRANSPORT_TCPSOCKET_H
#define TCP_TRANSPORT_TCPSOCKET_H

#include "stdio.h"
#include "link_platform_h_socket.h"
#include "unistd.h"
#include "Address.h"
#include "../Logger/Logger.h"

#if PLATFORM == PLATFORM_WINDOWS
typedef int socklen_t;
#endif

/**
 * Класс потокового сокета, который опирается на TCP
 */
class TCPSocket {
public:

    TCPSocket();

    TCPSocket(int handle);

    ~TCPSocket();

    /**
     *  Привязка сокета к конкретному порту
     * @param port - порт, по умолчанию 0, система
     * сама выделит порт
     * @return
     */
    bool Open(unsigned short port = 0);

    /**
     * Перевод сокета в неблокирующий режим
     * @param mode - 1 - неблокирующий
     * 0 - блокирующий
     * @return
     */
    bool NonBlocking(char mode = 1);

    /**
     *  Закрытие сокета
     */
    void Close();

    /**
     * Отправить пакет с данными
     * @param destination - назначение узла сети
     * @param data - пакет данных
     * @param size - количество байт в пакете
     * @return
     */
    bool Send(const Address &destination, const void *packet_data, int packet_size);

    /**
     * Читает данные из очереди сообщений
     * @param sender - отправитель
     * @param data - сюда будет помещены данные
     * @param size - максимальное кол-во байт для чтения
     * @return - количество прочитанных байт
     */
    int Receive(Address &sender, void *data, int size);

    /**
     * Подготовка сокета к принятию входящих соединений
     * Прослушивание порта
     * @param max_count_package_in_queue - максимальное количество пакетов
     * в очереди сообщений
     * @return
     */
    bool Listen(unsigned int max_count_package_in_queue);

    /**
     * Cоздает новый сокет, связанный с принятым соединением.
     * Для формирования нового сокета нужен
     * действующий сокет, который уже прослушивает порт.
     * @param address - адрес, откуда идет соединение
     * @return новый сокет
     */
    TCPSocket *Accept(Address &address);

    /**
     * Установка соединения
     * @param address
     * @return
     */
    bool Connect(const Address &address);

private:

    /*
     * Дискриптор сокета
     */
    int handle;
};


#endif //TCP_TRANSPORT_TCPSOCKET_H
