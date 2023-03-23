#pragma once

#include "Packet.hpp"
#include "fields/PacketField.hpp"
#include "PacketType.hpp"

#include <vector>
#include <memory>

namespace babel {

    class Deserializer {
        public:
            std::unique_ptr<Packet> deserialize(const char *data);
            std::unique_ptr<PacketField> deserializeField(const char *data);

        private:
            std::unique_ptr<PacketField> _nextField(const char *data, int *index);
    };
    
}
