#include "StringField.hpp"

using namespace babel;

StringField::StringField(std::string value) : _value(value) {}

const FieldType StringField::getType() const {
    return (FieldType::STRING);
}

const size_t StringField::getSize() const {
    return (sizeof(unsigned int) + this->_value.length());
}

const std::string StringField::serialize(bool showHeader) const {
    std::stringstream ss;

    if (showHeader) {
        ss << CharacterField(this->getType()).serialize(false);
        ss << UnsignedIntegerField(this->_value.length()).serialize(false);
    }

    for (char c: this->_value)
        ss << CharacterField(c).serialize(false);
    return (ss.str());
}

const std::string StringField::getValue() const {
    return (this->_value);
}
