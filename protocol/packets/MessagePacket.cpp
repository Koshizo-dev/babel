#include "MessagePacket.hpp"
#include "../fields/StringField.hpp"
#include "../fields/UnsignedInteger64Field.hpp"
#include "../serialization/Serializer.hpp"

#include <iostream>

using namespace babel;

MessagePacket::MessagePacket(std::string recipient, std::string content): MessagePacket("", recipient, content, 0) {}

MessagePacket::MessagePacket(std::string sender, std::string recipient, std::string content, std::uint64_t timestamp): _sender(sender), _recipient(recipient), _content(content), _timestamp(timestamp) {
}

const std::string MessagePacket::getSender() const {
    return (this->_sender);
}

const std::string MessagePacket::getRecipient() const {
    return (this->_recipient);
}

const std::string MessagePacket::getContent() const {
    return (this->_content);
}

const std::uint64_t MessagePacket::getTimestamp() const {
    return (this->_timestamp);
}

const PacketType MessagePacket::getType() const {
    return (PacketType::MESSAGE);
}

const std::string MessagePacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_sender);
    serializer << new StringField(this->_recipient);
    serializer << new StringField(this->_content);
    serializer << new UnsignedInteger64Field(this->_timestamp);
    return (serializer.serialize());
}

std::unique_ptr<Packet> MessagePacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 4)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);

    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *sender = static_cast<StringField*>(field.get());
    std::string senderName = sender->getValue();

    field = std::move(packetFields[1]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *recipient = static_cast<StringField*>(field.get());
    std::string recipientName = recipient->getValue();

    field = std::move(packetFields[2]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *content = static_cast<StringField*>(field.get());
    std::string contentString = content->getValue();

    field = std::move(packetFields[3]);
    if (field->getType() != FieldType::UNSIGNED_INTEGER_64)
        return (nullptr);
    UnsignedInteger64Field *timestamp = static_cast<UnsignedInteger64Field*>(field.get());
    std::uint64_t timestampt_t = timestamp->getValue();
    return (std::unique_ptr<Packet>(new MessagePacket(senderName, recipientName, contentString, timestampt_t)));
}
