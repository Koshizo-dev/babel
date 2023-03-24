#include "Transporter.hpp"

using namespace babel;

Transporter::Transporter(std::shared_ptr<EventManager> eventManager, std::unique_ptr<Socket> socket): _eventManager(eventManager), _socket(std::move(socket)) {
    this->_socket->setEventManager(this->_eventManager);
}

Transporter::~Transporter() {
    printf("in destructor!\n");
    this->sendMessage("DISCONNECT");
    this->_socket->closeConnection();
}

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
