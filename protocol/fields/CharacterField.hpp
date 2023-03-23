#pragma once

#include "PacketField.hpp"

namespace babel {

    class CharacterField: public PacketField {
        public:
            CharacterField(char value);

            const FieldType getType() const;
            const size_t getSize() const;
            const std::string serialize(bool showHeader = true) const;
            const char getValue() const;

            static CharacterField deserialize(const char *data) {
                return (CharacterField(data[0]));
            }

        private:
            const char _value;
    };
    
}
