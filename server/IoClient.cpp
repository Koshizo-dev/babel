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

const void IoClient::addContact(std::string username) {
    if (!this->isContactWith(username))
        this->_contacts.push_back(username);
}

const bool IoClient::isContactWith(std::string username) const {
    for (std::string contact: this->_contacts)
        if (contact == username)
            return (true);
    return (false);
}

const std::shared_ptr<Transporter> IoClient::getTransporter() const {
    return (this->_transporter);
}

const void IoClient::_handle() {
    if (this->_transporter == nullptr || this->_transporter->isClosed())
        return;
    this->_transporter->readMessage([this](std::string message) {
        if (message != "")
            this->_eventManager->handlePacket(this, message);
        return this->_handle();
    });
}
