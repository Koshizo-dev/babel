#include "Deserializer.hpp"
#include "fields/CharacterField.hpp"
#include "fields/StringField.hpp"
#include "fields/IntegerField.hpp"
#include <iostream>

using namespace babel;

std::unique_ptr<Packet> Deserializer::deserialize(const char *data) {
    int index = 0;

    CharacterField magic = CharacterField::deserialize(data);
    index += magic.getSize();
    if (magic.getValue() != 0x32)
        return (nullptr);

    CharacterField packetType = CharacterField::deserialize(&data[index]);
    index += packetType.getSize();

    std::vector<std::unique_ptr<PacketField>> fields = {};

    std::unique_ptr<PacketField> field = this->deserializeField(&data[index]);
    index += field->getSize();
    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *username = static_cast<StringField*>(field.get());
    std::cout << "string = [" << username->getValue() << "]" << std::endl;
    return nullptr;
}

std::unique_ptr<PacketField> Deserializer::deserializeField(const char *data) {
    FieldType type = static_cast<FieldType>(CharacterField::deserialize(&data[0]).getValue());

    switch (type) {
        case FieldType::CHARACTER:
            {
                CharacterField field = CharacterField::deserialize(&data[1]);
                return (std::unique_ptr<PacketField>(new CharacterField(field.getValue())));
            }
        case FieldType::INTEGER:
            {
                IntegerField field = IntegerField::deserialize(&data[1]);
                return (std::unique_ptr<PacketField>(new IntegerField(field.getValue())));
            }
        case FieldType::STRING:
            {
                StringField field = StringField::deserialize(&data[1]);
                return (std::unique_ptr<PacketField>(new StringField(field.getValue())));
            }
        }
    return (nullptr);
}
