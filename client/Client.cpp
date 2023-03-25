#include "Client.hpp"

using namespace babel;

Client::Client(std::string username) {
    this->_username = username;
}

const std::string Client::getUsername() const {
    return (this->_username);
}

Icon *Client::getIcon(int size) const {
    return (this->_generateIcon(size));
}

const std::vector<std::shared_ptr<Message>> Client::getMessages() const {
    return (this->_messages);
}

const void Client::addMessage(std::shared_ptr<Message> message) {
    this->_messages.push_back(message);
}

const bool Client::isChatting() const {
    return (this->_isChatting);
}

const bool Client::isInCall() const {
    return (this->_isInCall);
}

const bool Client::isChatWindow() const {
    return (this->_isChatWindow);
}

const void Client::setChatting(bool isChatting) {
    this->_isChatting = isChatting;
}

const void Client::setInCall(bool isInCall) {
    this->_isInCall = isInCall;
}

const void Client::setChatWindow(bool isChatWindow) {
    this->_isChatWindow = isChatWindow;
}

Icon *Client::_generateIcon(int size) const {
    return (new Icon(this->_username, nullptr, size));
}
