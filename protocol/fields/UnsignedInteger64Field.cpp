#include "UnsignedInteger64Field.hpp"
#include  "CharacterField.hpp"
#include "PacketField.hpp"

#include <iostream>
#include <sstream>

using namespace babel;

UnsignedInteger64Field::UnsignedInteger64Field(std::uint64_t value) : _value(value) {}

const FieldType UnsignedInteger64Field::getType() const {
    return (FieldType::UNSIGNED_INTEGER_64);
}

const size_t UnsignedInteger64Field::getSize() const {
    return (sizeof(this->_value));
}

const std::string UnsignedInteger64Field::serialize(bool showHeader) const {
    std::stringstream ss;

    char bytes[8];
    for (int i = 0; i < 8; i++)
        bytes[i] = static_cast<unsigned char>((this->_value >> (i * 8)) & 0xff);

    if (showHeader)
        ss << CharacterField(this->getType()).serialize(false);

    for (int i = 0; i < 8; i++)
        ss.write(&bytes[i], 1);

    return (ss.str());
}

const std::uint64_t UnsignedInteger64Field::getValue() const {
    return (this->_value);
}
