#pragma once

#include "ClientPacketHandler.hpp"
#include "../PacketManager.hpp"

#include <map>
#include <vector>

namespace babel {

    class ClientPacketManager: public PacketManager {
        public:
            ClientPacketManager(std::shared_ptr<ClientManager> clientManager);
    
            void handlePacket(Packet &packet) override;
            void registerHandler(PacketType packetType, std::shared_ptr<ClientPacketHandler> packetHandler);

        private:
            std::shared_ptr<ClientManager> _clientManager = nullptr;
            std::map<PacketType, std::shared_ptr<ClientPacketHandler>> _packetHandlers = {};
    };
    
}
