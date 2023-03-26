#pragma once

#include "PacketType.hpp"
#include "../fields/PacketField.hpp"

#include <string>
#include <vector>
#include <memory>

namespace babel {

    class Packet {
        public:
            Packet() {}
    
            virtual const PacketType getType() const = 0;
            virtual const std::string serialize() const = 0;
            virtual std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const = 0;
    };
    
}
