#include "Serializer.hpp"
#include "PacketType.hpp"
#include "fields/IntegerField.hpp"
#include "fields/CharacterField.hpp"
#include "fields/StringField.hpp"

#include <sstream>

using namespace babel;

Serializer::Serializer(PacketType type): _type(type) {}

std::string Serializer::serialize() {
    std::stringstream ss;
    int size = 0;
    char magic = 0x32;

    ss << CharacterField(magic).serialize(false);
    ss << CharacterField(this->_type).serialize(false);

    for (const PacketField *field: this->_fields)
        ss << field->serialize();
    return (ss.str());
}

Serializer &Serializer::operator<<(const PacketField *field) {
    this->_fields.push_back(field);
    return (*this);
}
