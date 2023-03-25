#include "ServerPacketManager.hpp"

#include "ServerPacketHandler.hpp"
#include "../../server/ServerManager.hpp"
#include "packets/LoginPacketHandler.hpp"
#include "packets/LogoutPacketHandler.hpp"
#include "packets/MessagePacketHandler.hpp"

using namespace babel;

ServerPacketManager::ServerPacketManager(std::shared_ptr<ServerManager> serverManager) {
    this->_serverManager = serverManager;

    this->registerHandler(PacketType::LOGIN, std::shared_ptr<ServerPacketHandler>(new LoginPacketHandler()));
    this->registerHandler(PacketType::LOGOUT, std::shared_ptr<ServerPacketHandler>(new LogoutPacketHandler()));
    this->registerHandler(PacketType::MESSAGE, std::shared_ptr<ServerPacketHandler>(new MessagePacketHandler()));
}

void ServerPacketManager::handlePacket(Packet &packet) {
    this->handleServerPacket(packet, nullptr);
}

void ServerPacketManager::handleServerPacket(Packet &packet, IoClient *origin) {
    auto iter = this->_packetHandlers.find(packet.getType());
    if (iter != this->_packetHandlers.end()) {
        auto packetHandler = iter->second;
        packetHandler->handle(packet, this->_serverManager, origin);
    }
}

void ServerPacketManager::registerHandler(PacketType packetType, std::shared_ptr<ServerPacketHandler> packetHandler) {
    this->_packetHandlers[packetType] = packetHandler;
}
