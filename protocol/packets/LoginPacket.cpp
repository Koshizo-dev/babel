#include "LoginPacket.hpp"
#include "../fields/IntegerField.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

LoginPacket::LoginPacket(std::string username) {
    this->_username = username;
}

std::string LoginPacket::getUsername() {
    return (this->_username);
}

PacketType LoginPacket::getType() {
    return (PacketType::LOGIN);
}

std::string LoginPacket::serialize() {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    return (serializer.serialize());
}

std::unique_ptr<Packet> LoginPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) {
    if (packetFields.size() != 1)
        return (nullptr); // TODO throw exception

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr); // TODO throw exception

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new LoginPacket(name->getValue())));
}
