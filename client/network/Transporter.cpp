#include "Transporter.hpp"

using namespace babel;

Transporter::Transporter(std::unique_ptr<Socket> socket): _socket(std::move(socket)) {}

bool Transporter::awaitingConnection() {
    return (this->_socket->awaitingConnection());
}

void Transporter::closeConnection() {
    this->_socket->closeConnection();
}

void Transporter::sendMessage(std::string message) {
    this->_socket->write(message);
    this->_socket->write("\r\n");
    this->_socket->flush();
}

std::string Transporter::readMessage() {
    // TODO
    return (nullptr);
}
