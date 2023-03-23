#include "PacketManager.hpp"

using namespace babel;

std::unique_ptr<Packet> PacketManager::deserialize(std::string &packet) {
    char const *data = packet.c_str();
    char magic = data[0];

    if (magic != 0x32)
        return (nullptr);

    return nullptr;
}

std::string PacketManager::serialize(Packet &packet) {
    return packet.serialize();
}
