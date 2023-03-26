#include "ServerPacketManager.hpp"

#include "ServerPacketHandler.hpp"
#include "../../server/ServerManager.hpp"
#include "packets/LoginPacketHandler.hpp"
#include "packets/LogoutPacketHandler.hpp"
#include "packets/ContactPacketHandler.hpp"
#include "packets/MessagePacketHandler.hpp"
#include "packets/CallUpPacketHandler.hpp"
#include "packets/HangUpPacketHandler.hpp"

using namespace babel;

ServerPacketManager::ServerPacketManager(std::shared_ptr<ServerManager> serverManager) {
    this->_serverManager = serverManager;

    this->registerHandler(PacketType::LOGIN, std::shared_ptr<ServerPacketHandler>(new LoginPacketHandler()));
    this->registerHandler(PacketType::LOGOUT, std::shared_ptr<ServerPacketHandler>(new LogoutPacketHandler()));
    this->registerHandler(PacketType::CONTACT, std::shared_ptr<ServerPacketHandler>(new ContactPacketHandler()));
    this->registerHandler(PacketType::MESSAGE, std::shared_ptr<ServerPacketHandler>(new MessagePacketHandler()));
    this->registerHandler(PacketType::CALL_UP, std::shared_ptr<ServerPacketHandler>(new CallUpPacketHandler()));
    this->registerHandler(PacketType::HANG_UP, std::shared_ptr<ServerPacketHandler>(new HangUpPacketHandler()));
}

const void ServerPacketManager::handlePacket(Packet &packet) const {
    this->handleServerPacket(packet, nullptr);
}

const void ServerPacketManager::handleServerPacket(Packet &packet, IoClient *origin) const {
    auto iter = this->_packetHandlers.find(packet.getType());
    if (iter != this->_packetHandlers.end()) {
        auto packetHandler = iter->second;
        packetHandler->handle(packet, this->_serverManager, origin);
    }
}

const void ServerPacketManager::registerHandler(PacketType packetType, std::shared_ptr<ServerPacketHandler> packetHandler) {
    this->_packetHandlers[packetType] = packetHandler;
}
