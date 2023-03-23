#include "CharacterField.hpp"
#include <sstream>

using namespace babel;

CharacterField::CharacterField(char value) : _value(value) {}

const FieldType CharacterField::getType() const {
    return (FieldType::CHARACTER);
}

const size_t CharacterField::getSize() const {
    return (sizeof(char));
}

const std::string CharacterField::serialize(bool showHeader) const {
    std::stringstream ss;
    char typeId = this->getType();

    if (showHeader)
        ss.write(&typeId, 1);
    ss.write(&this->_value, 1);
    return (ss.str());
}

const char CharacterField::getValue() const {
    return (this->_value);
}
