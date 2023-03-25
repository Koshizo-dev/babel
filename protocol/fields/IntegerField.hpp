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
                int value = 0;
                if (PacketField::isBigEndian())
                    for (int i = 3; i >= 0; i--)
                        value |= static_cast<int>(static_cast<unsigned char>(data[i])) << ((3 - i) * 8);
                else
                    for (int i = 0; i < 4; i++)
                        value |= static_cast<int>(static_cast<unsigned char>(data[i])) << (i * 8);

                return (IntegerField(value));
            }

        private:
            const int _value;
    };
    
}
