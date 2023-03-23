#pragma once

#include "fields/PacketField.hpp"
#include "PacketType.hpp"

#include <vector>
#include <memory>

namespace babel {

    class Serializer {
        public:
            Serializer(PacketType type);

            std::string serialize();
            Serializer &operator<<(const PacketField *field);

        private:
            const PacketType _type;
            std::vector<const PacketField*> _fields = {};
    };
    
}
