#include "Client.hpp"

using namespace babel;

Client::Client(std::string username) {
    this->_username = username;
}

std::string Client::getUsername() {
    return (this->_username);
}

std::shared_ptr<Icon> Client::getIcon() {
    if (this->_icon == nullptr)
        this->_icon = this->_generateIcon();
    return (this->_icon);
}

std::shared_ptr<Icon> Client::_generateIcon() {
    return (std::shared_ptr<Icon>(new Icon(this->_username, nullptr)));
}
