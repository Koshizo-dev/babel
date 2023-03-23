#pragma once

#include "packets/Packet.hpp"
#include "PacketHandler.hpp"

#include <memory>

namespace babel {

    class PacketManager {
        public:
            virtual void handlePacket(Packet &packet) = 0;

            std::unique_ptr<Packet> deserialize(std::string &packet);
            std::string serialize(Packet &packet);
    };
    
}

