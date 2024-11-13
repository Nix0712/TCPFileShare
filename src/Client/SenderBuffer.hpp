#ifndef CLINET_SENDER_BUFFER_HPP
#define CLINET_SENDER_BUFFER_HPP

#include "boost/asio/io_context.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class ClientSenderBuffer{
    ClientSenderBuffer(tcp::socket socket) : socket(std::move(socket)) {};

    void sendFile(std::string message);

    ~ClientSenderBuffer();

private:
    tcp::socket socket;

    void encodeFile(std::string message);

};

#endif
