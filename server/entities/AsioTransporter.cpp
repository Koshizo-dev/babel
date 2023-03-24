#include "AsioTransporter.hpp"

#include <iostream>

using namespace babel;

AsioTransporter::AsioTransporter(asio::io_service &io_service) : _socket(io_service) {}

asio::ip::tcp::socket &AsioTransporter::socket() {
    return (this->_socket);
}

void AsioTransporter::sendMessage(std::string message) {
    std::cout << "writing!" << std::endl;
    asio::async_write(this->_socket, asio::buffer(message),
        [this](std::error_code ec, std::size_t /*length*/) {
            if (!ec)
                this->readMessage();
        });
}

std::string AsioTransporter::readMessage() {
    std::cout << "reading!" << std::endl;
    asio::async_read_until(this->_socket, this->_buf, "\r\n",
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::string message = std::string(
                    asio::buffer_cast<const char *>(this->_buf.data()),
                    length);
                this->_buf.consume(length);
                printf("packet = ");
                for (int i = 0; i < message.length(); i++)
                    printf("[%d]", message[i]);
                printf("\n");
                this->sendMessage(message);
            }
        });
    return ("");
}
