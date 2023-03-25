#include "LogoutPacket.hpp"
#include "../fields/IntegerField.hpp"
#include "../fields/StringField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

LogoutPacket::LogoutPacket() {
}

PacketType LogoutPacket::getType() {
    return (PacketType::LOGOUT);
}

std::string LogoutPacket::serialize() {
    Serializer serializer(this->getType());

    return (serializer.serialize());
}

std::unique_ptr<Packet> LogoutPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) {
    if (packetFields.size() != 0)
        return (nullptr);

    return (std::unique_ptr<Packet>(new LogoutPacket()));
}
