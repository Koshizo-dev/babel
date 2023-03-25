#include "IntegerField.hpp"
#include  "CharacterField.hpp"
#include "PacketField.hpp"

#include <sstream>

using namespace babel;

IntegerField::IntegerField(int value) : _value(value) {}

const FieldType IntegerField::getType() const {
    return (FieldType::INTEGER);
}

const size_t IntegerField::getSize() const {
    return (sizeof(this->_value));
}

const std::string IntegerField::serialize(bool showHeader) const {
    std::stringstream ss;

    char bytes[4];
    for (int i = 0; i < 4; i++)
        bytes[i] = static_cast<unsigned char>((this->_value >> (i * 8)) & 0xff);

    if (showHeader)
        ss << CharacterField(this->getType()).serialize(false);

    for (int i = 0; i < 4; i++)
        ss.write(&bytes[i], 1);

    return (ss.str());
}

const int IntegerField::getValue() const {
    return (this->_value);
}
