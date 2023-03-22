#include "Client.hpp"

#include <iostream>

using namespace babel;

Client::Client(std::shared_ptr<Transporter> transporter) {
    this->_transporter = transporter;

    std::cout << "Client initialized!" << std::endl;

    this->_transporter->readMessage();
}

std::shared_ptr<Transporter> Client::getTransporter() {
    return (this->_transporter);
}
