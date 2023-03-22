#include "AsioTransporter.hpp"

#include <iostream>

using namespace babel;

AsioTransporter::AsioTransporter(asio::io_service &io_service) : _socket(io_service) {}

asio::ip::tcp::socket &AsioTransporter::socket() {
    return (this->_socket);
}

void AsioTransporter::sendMessage(std::string message) {
    asio::async_write(this->_socket, asio::buffer(message),
        [this](std::error_code ec, std::size_t /*length*/) {
            if (!ec)
                this->readMessage();
        });
}

std::string AsioTransporter::readMessage() {
    std::cout << "reading!" << std::endl;
    asio::async_read_until(this->_socket, this->_buf, "\n",
        [this](std::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                std::string message = std::string(
                    asio::buffer_cast<const char *>(this->_buf.data()),
                    this->_buf.size());
               std::cout << "Received: " << message << "\n";
               this->sendMessage("Echo: " + message);
            }
        });
    return ("");
}
