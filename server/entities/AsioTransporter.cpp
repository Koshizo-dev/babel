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
    });
}

void AsioTransporter::readMessage(std::function<void(std::string)> callback) {
    asio::async_read_until(this->_socket, this->_buf, "\r\n",
        [this, callback](std::error_code ec, std::size_t length) {
            if (ec) {
                callback("");
                return;
            }
            std::string message = std::string(
                asio::buffer_cast<const char *>(this->_buf.data()),
                length-2);
            this->_buf.consume(length);
            callback(message);
    });
}