#pragma once

#include "PacketField.hpp"

namespace babel {

    class UnsignedInteger64Field: public PacketField {
        public:
            UnsignedInteger64Field(std::uint64_t value);

            const FieldType getType() const override;
            const size_t getSize() const override;
            const std::string serialize(bool showHeader = true) const override;
            const std::uint64_t getValue() const;

            static UnsignedInteger64Field deserialize(char const *data) {
                std::uint64_t value = 0;

                if (PacketField::isBigEndian())
                    for (int i = 7; i >= 0; i--)
                        value |= static_cast<std::uint64_t>(static_cast<unsigned char>(data[i])) << ((7 - i) * 8);
                else
                    for (int i = 0; i < 8; i++)
                        value |= static_cast<std::uint64_t>(static_cast<unsigned char>(data[i])) << (i * 8);
                return (UnsignedInteger64Field(value));
            }

        private:
            const std::uint64_t _value;
    };
    
}
