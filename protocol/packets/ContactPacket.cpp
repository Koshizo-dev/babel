#include "ContactPacket.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

ContactPacket::ContactPacket(std::string username) {
    this->_username = username;
}

std::string ContactPacket::getUsername() {
    return (this->_username);
}

PacketType ContactPacket::getType() {
    return (PacketType::CONTACT);
}

std::string ContactPacket::serialize() {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    return (serializer.serialize());
}

std::unique_ptr<Packet> ContactPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new ContactPacket(name->getValue())));
}
