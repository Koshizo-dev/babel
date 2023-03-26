#include "LoginErrorPacket.hpp"
#include "../fields/IntegerField.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

LoginErrorPacket::LoginErrorPacket(std::string error): _error(error) {
}

const std::string LoginErrorPacket::getError() const {
    return (this->_error);
}

const PacketType LoginErrorPacket::getType() const {
    return (PacketType::LOGIN_ERROR);
}

const std::string LoginErrorPacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_error);
    return (serializer.serialize());
}

std::unique_ptr<Packet> LoginErrorPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new LoginErrorPacket(name->getValue())));
}
