#pragma once

#include "packets/Packet.hpp"
#include "PacketHandler.hpp"

#include <memory>

namespace babel {

    class PacketManager {
        public:
            virtual const void handlePacket(Packet &packet) const = 0;

            std::unique_ptr<Packet> deserialize(std::string &packet) const;
            const std::string serialize(Packet &packet) const;
    };
    
}

