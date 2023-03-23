#pragma once

#include "../packets/Packet.hpp"

#include <vector>
#include <memory>

namespace babel {

    class Deserializer {
        public:
            std::unique_ptr<Packet> deserialize(PacketType packetType, std::vector<std::unique_ptr<PacketField>> fields);
            std::unique_ptr<PacketField> deserializeField(const char *data);
            std::unique_ptr<PacketField> nextField(const char *data, int *index);
    };
    
}
