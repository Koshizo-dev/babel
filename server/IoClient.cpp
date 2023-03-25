#include "IoClient.hpp"
#include "EventManager.hpp"
#include "TransporterError.hpp"

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
    if (this->_transporter->isClosed())
        return;
    this->_transporter->readMessage([this](std::string message) {
        if (message != "")
            this->_eventManager->handlePacket(this, message);
        return this->_handle();
    });
}
