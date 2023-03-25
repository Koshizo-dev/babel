#pragma once

#include "../PacketHandler.hpp"
#include "../packets/Packet.hpp"

#include <iostream>

namespace babel {

    class ServerManager;
    class IoClient;

    class ServerPacketHandler : public PacketHandler {
        public:
            virtual const void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const = 0;
    };
    
}
