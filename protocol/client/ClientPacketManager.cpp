#include "ClientPacketManager.hpp"

#include "ClientPacketHandler.hpp"
#include "packets/LoginPacketHandler.hpp"
#include "packets/LoginErrorPacketHandler.hpp"
#include "packets/LogoutPacketHandler.hpp"
#include "packets/ContactPacketHandler.hpp"
#include "packets/MessagePacketHandler.hpp"

using namespace babel;

ClientPacketManager::ClientPacketManager(std::shared_ptr<ClientManager> clientManager) {
    this->_clientManager = clientManager;

    this->registerHandler(PacketType::LOGIN, std::shared_ptr<ClientPacketHandler>(new LoginPacketHandler()));
    this->registerHandler(PacketType::LOGIN_ERROR, std::shared_ptr<ClientPacketHandler>(new LoginErrorPacketHandler()));
    this->registerHandler(PacketType::LOGOUT, std::shared_ptr<ClientPacketHandler>(new LogoutPacketHandler()));
    this->registerHandler(PacketType::CONTACT, std::shared_ptr<ClientPacketHandler>(new ContactPacketHandler()));
    this->registerHandler(PacketType::MESSAGE, std::shared_ptr<ClientPacketHandler>(new MessagePacketHandler()));
}

const void ClientPacketManager::handlePacket(Packet &packet) const {
    auto iter = this->_packetHandlers.find(packet.getType());
    if (iter != this->_packetHandlers.end()) {
        auto packetHandler = iter->second;
        packetHandler->handle(packet, this->_clientManager);
    }
}

const void ClientPacketManager::registerHandler(PacketType packetType, std::shared_ptr<ClientPacketHandler> packetHandler) {
    this->_packetHandlers[packetType] = packetHandler;
}
