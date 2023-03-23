#pragma once

#include "PacketType.hpp"
#include "fields/PacketField.hpp"

#include <string>
#include <vector>
#include <memory>

namespace babel {

    class Packet {
        public:
            Packet() {}
    
            virtual PacketType getType() = 0;
            virtual std::string serialize() = 0;
            virtual std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) = 0;
    };
    
}
