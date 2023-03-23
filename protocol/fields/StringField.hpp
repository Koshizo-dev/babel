#pragma once

#include "PacketField.hpp"
#include "IntegerField.hpp"
#include "CharacterField.hpp"

#include <sstream>

namespace babel {

    class StringField: public PacketField {
        public:
            StringField(std::string value);

            const FieldType getType() const override;
            const size_t getSize() const override;
            const std::string serialize(bool showHeader = true) const override;
            const std::string getValue() const;

            static StringField deserialize(char const *data) {
                std::stringstream ss;
                IntegerField size = IntegerField::deserialize(data);

                for (int i = 0; i < size.getValue(); i++)
                    ss << CharacterField::deserialize(&data[i+size.getSize()]).getValue();

                return (StringField(ss.str()));
            }

        private:
            const std::string _value;
    };
    
}
