#include "AsioTransporter.hpp"
#include "../TransporterError.hpp"

#include <iostream>

using namespace babel;

AsioTransporter::AsioTransporter(asio::io_service &io_service) : _socket(io_service) {}

asio::ip::tcp::socket &AsioTransporter::socket() {
    return (this->_socket);
}

const void AsioTransporter::sendMessage(std::string message) {
    this->_newWrite();
    message += "\r\n";
    asio::async_write(this->_socket, asio::buffer(message),
        [this](std::error_code ec, std::size_t /*length*/) {
            this->_endWrite();
    });
}

const void AsioTransporter::readMessage(std::function<void(std::string)> callback) {
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

const void AsioTransporter::close() {

    try {
        std::unique_lock<std::mutex> lock(this->_mutex);
        this->_socket.close();
        this->_isClosed = true;
    } catch (asio::system_error &error) {}

}

const bool AsioTransporter::isClosed() const {
    return (this->_isClosed);
}

const void AsioTransporter::_newWrite() {
    std::unique_lock<std::mutex> lock(this->_mutex);
    this->_writesProcessing++;
}

const void AsioTransporter::_endWrite() {
    {
        std::unique_lock<std::mutex> lock(this->_mutex);
        _writesProcessing--;
    }
    this->_cv.notify_all();
}
