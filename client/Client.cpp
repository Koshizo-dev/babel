#include "Client.hpp"

using namespace babel;

Client::Client(std::string username) {
    this->_username = username;
}

std::string Client::getUsername() {
    return (this->_username);
}

Icon *Client::getIcon(int size) {
    return (this->_generateIcon(size));
}

std::vector<std::shared_ptr<Message>> Client::getMessages() {
    return (this->_messages);
}

void Client::addMessage(std::shared_ptr<Message> message) {
    // std::lock_guard<std::mutex> lock(this->_mutex);
    this->_messages.push_back(message);
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

Icon *Client::_generateIcon(int size) {
    return (new Icon(this->_username, nullptr, size));
}
