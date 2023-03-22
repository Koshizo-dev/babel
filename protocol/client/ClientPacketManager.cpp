#include "ClientPacketManager.hpp"

#include "ClientPacketHandler.hpp"
#include "packets/LoginPacketHandler.hpp"

using namespace babel;

ClientPacketManager::ClientPacketManager(std::shared_ptr<ClientManager> clientManager) {
    this->_clientManager = clientManager;

    this->registerHandler(PacketType::LOGIN, std::shared_ptr<ClientPacketHandler>(new LoginPacketHandler()));
}

void ClientPacketManager::handlePacket(Packet &packet) {
    auto iter = this->_packetHandlers.find(packet.getType());
    if (iter != this->_packetHandlers.end()) {
        auto packetHandler = iter->second;
        packetHandler->handle(packet, this->_clientManager);
    }
}

void ClientPacketManager::registerHandler(PacketType packetType, std::shared_ptr<ClientPacketHandler> packetHandler) {
    this->_packetHandlers[packetType] = packetHandler;
}

std::unique_ptr<Packet> ClientPacketManager::deserialize(std::string &packet) {
    return nullptr;
}

std::string ClientPacketManager::serialize(Packet &packet) {
    return packet.serialize();
}
