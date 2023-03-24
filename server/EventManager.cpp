#include "EventManager.hpp"
#include <iostream>

using namespace babel;

EventManager::EventManager(std::shared_ptr<ServerPacketManager> packetManager): _packetManager(packetManager) {
}

void EventManager::handlePacket(IoClient *origin, std::string serialized) {
    std::unique_ptr<Packet> packet = this->_packetManager->deserialize(serialized);
    if (packet == nullptr) {
        std::cerr << "Packet invalid !" << std::endl;
        return;
    }
    this->_packetManager->handleServerPacket(*packet, origin);
}
