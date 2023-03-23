#include "LoginPacket.hpp"
#include "../fields/IntegerField.hpp"
#include "../fields/StringField.hpp"
#include "../Serializer.hpp"

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

std::unique_ptr<Packet> LoginPacket::deserialize(std::string &packet) {
    // TODO DESERIALIZE, RETURN NULL IF NOT THE SAME PACKET TYPE FIRST, AND THEN DESERIALIZE
    return nullptr;
}
