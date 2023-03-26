#pragma once

#include <string>

namespace babel {

    enum FieldType {
        CHARACTER,
        INTEGER,
        UNSIGNED_INTEGER,
        UNSIGNED_INTEGER_64,
        STRING,
    };

    class PacketField {
        public:
            virtual const FieldType getType() const = 0;
            virtual const size_t getSize() const = 0;
            virtual const std::string serialize(bool showHeader = true) const = 0;
    
            static bool isBigEndian(){
                uint16_t word = 1; // 0x0001
                uint8_t *first_byte = (uint8_t*) &word; // points to the first byte of word
                return !(*first_byte); // true if the first byte is zero
            }
    
    };

}
