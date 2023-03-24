#include "IoClient.hpp"
#include "EventManager.hpp"

#include <iostream>

using namespace babel;

IoClient::IoClient(std::shared_ptr<EventManager> eventManager, std::shared_ptr<Transporter> transporter) {
    this->_eventManager = eventManager;
    this->_transporter = transporter;

    this->_handle();
}

std::shared_ptr<Transporter> IoClient::getTransporter() {
    return (this->_transporter);
}

void IoClient::_handle() {
    this->_transporter->readMessage([this](std::string message) {
        this->_eventManager->handlePacket(this, message);
        this->_handle();
    });
}
