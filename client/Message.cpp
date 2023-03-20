#include "Message.hpp"
#include "Client.hpp"

using namespace babel;

Message::Message(std::shared_ptr<Client> author, std::string content, long timestamp, bool isDelivered) {
    this->_author = author;
    this->_content = content;
    this->_timestamp = timestamp;
    this->_isDelivered = isDelivered;
}

std::shared_ptr<Client> Message::getAuthor() {
    return (this->_author);
}

std::string Message::getContent() {
    return (this->_content);
}

long Message::getTimestamp() const {
    return (this->_timestamp);
}

bool Message::isDelivered() {
    return (this->_isDelivered);
}

void Message::setDelivered(bool isDelivered) {
    this->_isDelivered = isDelivered;
}
