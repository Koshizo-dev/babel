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

bool Client::isChatting() {
    return (this->_isChatting);
}

bool Client::isInCall() {
    return (this->_isInCall);
}

bool Client::isChatWindow() {
    return (this->_isChatWindow);
}

void Client::setChatting(bool isChatting) {
    this->_isChatting = isChatting;
}

void Client::setInCall(bool isInCall) {
    this->_isInCall = isInCall;
}

void Client::setChatWindow(bool isChatWindow) {
    this->_isChatWindow = isChatWindow;
}

std::shared_ptr<Icon> Client::_generateIcon() {
    return (std::shared_ptr<Icon>(new Icon(this->_username, nullptr)));
}
