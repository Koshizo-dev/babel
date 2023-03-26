#include "ContactPacket.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

ContactPacket::ContactPacket(std::string username): _username(username) {
}

const std::string ContactPacket::getUsername() const {
    return (this->_username);
}

const PacketType ContactPacket::getType() const {
    return (PacketType::CONTACT);
}

const std::string ContactPacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    return (serializer.serialize());
}

std::unique_ptr<Packet> ContactPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new ContactPacket(name->getValue())));
}
