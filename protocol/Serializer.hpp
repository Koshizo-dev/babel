#pragma once

#include "fields/PacketField.hpp"
#include "PacketType.hpp"

#include <memory>
#include <vector>

namespace babel {

    class Serializer {
        public:
            Serializer(PacketType type);

            std::string serialize();
            Serializer &operator<<(PacketField *field);

        private:
            const PacketType _type;
            std::vector<std::unique_ptr<PacketField>> _fields = {};
    };
    
}
