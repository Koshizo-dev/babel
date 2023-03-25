#include "EventManager.hpp"
#include <iostream>

using namespace babel;

EventManager::EventManager(std::shared_ptr<ServerPacketManager> packetManager): _packetManager(packetManager) {
}

void EventManager::handlePacket(IoClient *origin, std::string serialized) {
    std::unique_ptr<Packet> packet = this->_packetManager->deserialize(serialized);
    if (packet == nullptr) {
        std::string username = origin->username;
        if (username == "")
            username = "Unknown user";
        std::cerr << "[" << username << "]: Packet invalid ! | raw: {" << serialized << "} | bytes: {";
        for (int i = 0; i < serialized.length(); i++)
            std::cerr << "[" << static_cast<int>(serialized[i]) << "]";
        std::cerr << "}" << std::endl;
        return;
    }
    this->_packetManager->handleServerPacket(*packet, origin);
}
