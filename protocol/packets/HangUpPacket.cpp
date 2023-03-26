#include "HangUpPacket.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

HangUpPacket::HangUpPacket(std::string username): _username(username) {
}

const std::string HangUpPacket::getUsername() const {
    return (this->_username);
}

const PacketType HangUpPacket::getType() const {
    return (PacketType::HANG_UP);
}

const std::string HangUpPacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    return (serializer.serialize());
}

std::unique_ptr<Packet> HangUpPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 1)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);

    StringField *name = static_cast<StringField*>(field.get());

    return (std::unique_ptr<Packet>(new HangUpPacket(name->getValue())));
}
