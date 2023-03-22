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

            std::unique_ptr<Packet> deserialize(std::string &packet) override;
            std::string serialize(Packet &packet) override;
        private:
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    
            std::map<PacketType, std::shared_ptr<ClientPacketHandler>> _packetHandlers = {};
            std::vector<Packet> _packets = {};
    };
    
}
