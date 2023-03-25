#include "Message.hpp"
#include "Client.hpp"

using namespace babel;

Message::Message(std::shared_ptr<Client> author, std::string content, long timestamp, bool isDelivered) {
    this->_author = author;
    this->_content = content;
    this->_timestamp = timestamp;
    this->_isDelivered = isDelivered;
}

const std::shared_ptr<Client> Message::getAuthor() const {
    return (this->_author);
}

const std::string Message::getContent() const {
    return (this->_content);
}

const long Message::getTimestamp() const {
    return (this->_timestamp);
}

const bool Message::isDelivered() const {
    return (this->_isDelivered);
}

const void Message::setDelivered(bool isDelivered) {
    this->_isDelivered = isDelivered;
}
