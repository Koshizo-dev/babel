#pragma once

#include "../PacketHandler.hpp"
#include "../packets/Packet.hpp"

#include <iostream>

namespace babel {

    class ServerManager;
    class IoClient;

    class ServerPacketHandler : public PacketHandler {
        public:
            virtual void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) = 0;
    };
    
}
