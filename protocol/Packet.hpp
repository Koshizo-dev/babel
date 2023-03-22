#pragma once

#include "PacketType.hpp"

#include <string>
#include <memory>

namespace babel {

    class Packet {
        public:
            virtual PacketType getType() = 0;
            virtual std::string serialize() = 0;
            virtual std::unique_ptr<Packet> deserialize(std::string &packet) = 0;
    };
    
}
