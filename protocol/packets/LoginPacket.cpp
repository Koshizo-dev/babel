#include "LoginPacket.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

LoginPacket::LoginPacket(std::string username): _username(username) {
}

const std::string LoginPacket::getUsername() const {
    return (this->_username);
}

const PacketType LoginPacket::getType() const {
    return (PacketType::LOGIN);
}

const std::string LoginPacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    return (serializer.serialize());
}

std::unique_ptr<Packet> LoginPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new LoginPacket(name->getValue())));
}
