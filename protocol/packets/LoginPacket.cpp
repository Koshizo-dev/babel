#include "LoginPacket.hpp"

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
    return (this->_username); // TODO SERIALIZE
}

std::unique_ptr<Packet> LoginPacket::deserialize(std::string &packet) {
    // TODO DESERIALIZE, RETURN NULL IF NOT THE SAME PACKET TYPE FIRST, AND THEN DESERIALIZE
    return nullptr;
}
