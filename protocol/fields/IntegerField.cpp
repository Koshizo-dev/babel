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
    char byte1 = (this->_value & 0x000000ff);
    char byte2 = ((this->_value & 0x0000ff00) >> 8);
    char byte3 = ((this->_value & 0x00ff0000) >> 16);
    char byte4 = ((this->_value & 0xff000000) >> 24);

    if (showHeader)
        ss << CharacterField(this->getType()).serialize(false);

    ss.write(&byte1, 1);
    ss.write(&byte2, 1);
    ss.write(&byte3, 1);
    ss.write(&byte4, 1);
    return (ss.str());
}

const int IntegerField::getValue() const {
    return (this->_value);
}
