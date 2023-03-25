#include "LoginErrorPacket.hpp"
#include "../fields/IntegerField.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

LoginErrorPacket::LoginErrorPacket(std::string error) {
    this->_error = error;
}

std::string LoginErrorPacket::getError() {
    return (this->_error);
}

PacketType LoginErrorPacket::getType() {
    return (PacketType::LOGIN_ERROR);
}

std::string LoginErrorPacket::serialize() {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_error);
    return (serializer.serialize());
}

std::unique_ptr<Packet> LoginErrorPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new LoginErrorPacket(name->getValue())));
}
