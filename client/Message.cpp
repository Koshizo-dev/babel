#include "Message.hpp"

using namespace babel;

Message::Message(std::string content, long timestamp, bool isDelivered) {
    this->_content = content;
    this->_timestamp = timestamp;
    this->_isDelivered = isDelivered;
}

std::string Message::getContent() {
    return (this->_content);
}

long Message::getTimestamp() {
    return (this->_timestamp);
}

bool Message::isDelivered() {
    return (this->_isDelivered);
}

void Message::setDelivered(bool isDelivered) {
    this->_isDelivered = isDelivered;
}
