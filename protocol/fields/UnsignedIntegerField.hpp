#pragma once

#include "PacketField.hpp"

namespace babel {

    class UnsignedIntegerField: public PacketField {
        public:
            UnsignedIntegerField(unsigned int value);

            const FieldType getType() const override;
            const size_t getSize() const override;
            const std::string serialize(bool showHeader = true) const override;
            const int getValue() const;

            static UnsignedIntegerField deserialize(char const *data) {
                unsigned int value = 0;
                if (PacketField::isBigEndian())
                    for (int i = 3; i >= 0; i--)
                        value |= static_cast<unsigned int>(static_cast<unsigned char>(data[i])) << ((3 - i) * 8);
                else
                    for (int i = 0; i < 4; i++)
                        value |= static_cast<unsigned int>(static_cast<unsigned char>(data[i])) << (i * 8);

                return (UnsignedIntegerField(value));
            }

        private:
            const unsigned int _value;
    };
    
}
