#pragma once

#include "Packet.hpp"
#include "PacketHandler.hpp"

#include <memory>

namespace babel {

    class PacketManager {
        public:
            virtual void handlePacket(Packet &packet) = 0;

            virtual std::unique_ptr<Packet> deserialize(std::string &packet) = 0;
            virtual std::string serialize(Packet &packet) = 0;
    };
    
}

