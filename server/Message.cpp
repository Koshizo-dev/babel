#include "Message.hpp"

using namespace babel;

Message::Message(const std::string sender, const std::string recipient, const std::string content, const std::uint64_t timestamp): _sender(sender), _recipient(recipient), _content(content), _timestamp(timestamp) {
}

const std::string Message::getSender() const {
    return (this->_sender);
}

const std::string Message::getRecipient() const {
    return (this->_recipient);
}

const std::string Message::getContent() const {
    return (this->_content);
}

const std::uint64_t Message::getTimestamp() const {
    return (this->_timestamp);
}