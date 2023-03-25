#include "Serializer.hpp"
#include "../fields/CharacterField.hpp"

#include <sstream>

using namespace babel;

Serializer::Serializer(PacketType type): _type(type) {}

const std::string Serializer::serialize() {
    std::stringstream ss;
    int size = 0;
    char magic = 0x32;

    ss << CharacterField(magic).serialize(false);
    ss << CharacterField(this->_type).serialize(false);

    for (std::unique_ptr<PacketField> &field: this->_fields)
        ss << field->serialize();
    return (ss.str());
}

Serializer &Serializer::operator<<(PacketField *field) {
    this->_fields.push_back(std::unique_ptr<PacketField>(field));
    return (*this);
}
