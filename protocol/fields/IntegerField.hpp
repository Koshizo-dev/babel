#pragma once

#include "PacketField.hpp"

namespace babel {

    class IntegerField: public PacketField {
        public:
            IntegerField(int value);

            const FieldType getType() const override;
            const size_t getSize() const override;
            const std::string serialize(bool showHeader = true) const override;
            const int getValue() const;

            static IntegerField deserialize(char const *data) {
                int value;

                value = (data[0] & 0xff) | ((data[1] & 0xff) << 8) | ((data[2] & 0xff) << 16) | ((data[3] & 0xff) << 24);

                return (IntegerField(value));
            }

        private:
            const int _value;
    };
    
}
