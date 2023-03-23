#pragma once

#include <string>

namespace babel {

    enum FieldType {
        CHARACTER,
        INTEGER,
        STRING,
    };

    class PacketField {
        public:
            virtual const FieldType getType() const = 0;
            virtual const size_t getSize() const = 0;
            virtual const std::string serialize(bool showHeader = true) const = 0;
    };

}
