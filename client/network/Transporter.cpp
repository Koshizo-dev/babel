#include "Transporter.hpp"
#include "../../protocol/packets/LogoutPacket.hpp"

using namespace babel;

Transporter::Transporter(std::shared_ptr<EventManager> eventManager, std::unique_ptr<Socket> socket): _eventManager(eventManager), _socket(std::move(socket)) {
    this->_socket->setEventManager(this->_eventManager);
}

Transporter::~Transporter() {
    LogoutPacket packet;
    this->sendMessage(packet.serialize());
    this->_socket->closeConnection();
}

const bool Transporter::awaitingConnection() {
    return (this->_socket->awaitingConnection());
}

const void Transporter::closeConnection() {
    this->_socket->closeConnection();
}

const void Transporter::sendMessage(std::string message) {
    this->_socket->write(message);
    this->_socket->write("\r\n");
    this->_socket->flush();
}
