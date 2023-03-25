#include "EventManager.hpp"
#include "ClientManager.hpp"
#include <iostream>

using namespace babel;

EventManager::EventManager(std::shared_ptr<ClientManager> clientManager, std::shared_ptr<PacketManager> packetManager): _packetManager(packetManager), _clientManager(clientManager) {
}

void EventManager::handlePacket(std::string serialized) {
    std::unique_ptr<Packet> packet = this->_packetManager->deserialize(serialized);
    if (packet == nullptr) {
        std::cerr << "Invalid packet!" << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(this->_clientManager->mutex);
    this->_packetManager->handlePacket(*packet);
}
