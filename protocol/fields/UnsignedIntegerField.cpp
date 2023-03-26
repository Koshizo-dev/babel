#include "UnsignedIntegerField.hpp"
#include  "CharacterField.hpp"
#include "PacketField.hpp"

#include <sstream>

using namespace babel;

UnsignedIntegerField::UnsignedIntegerField(unsigned int value) : _value(value) {}

const FieldType UnsignedIntegerField::getType() const {
    return (FieldType::UNSIGNED_INTEGER);
}

const size_t UnsignedIntegerField::getSize() const {
    return (sizeof(this->_value));
}

const std::string UnsignedIntegerField::serialize(bool showHeader) const {
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

const int UnsignedIntegerField::getValue() const {
    return (this->_value);
}
