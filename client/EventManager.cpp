#include "EventManager.hpp"
#include <iostream>

using namespace babel;

EventManager::EventManager(std::shared_ptr<PacketManager> packetManager): _packetManager(packetManager) {
}

void EventManager::handlePacket(std::string serialized) {
    std::unique_ptr<Packet> packet = this->_packetManager->deserialize(serialized);
    if (packet == nullptr) {
        std::cerr << "Invalid packet!" << std::endl;
        return;
    }
    this->_packetManager->handlePacket(*packet);
}
