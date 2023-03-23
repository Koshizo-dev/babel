#include "Deserializer.hpp"
#include "../fields/CharacterField.hpp"
#include "../fields/StringField.hpp"
#include "../fields/IntegerField.hpp"
#include "../packets/LoginPacket.hpp"

using namespace babel;

std::unique_ptr<Packet> Deserializer::deserialize(PacketType packetType, std::vector<std::unique_ptr<PacketField>> packetFields) {
    switch (packetType) {
        case PacketType::LOGIN:
            return (LoginPacket().deserialize(std::move(packetFields)));
    }

    return (nullptr);
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

std::unique_ptr<PacketField> Deserializer::nextField(const char *data, int *index) {
    if (data[0] == 0)
        return (nullptr);
    std::unique_ptr<PacketField> field = nullptr;
    if ((field = this->deserializeField(data)) == nullptr)
        return (nullptr);
    *index = *index + field->getSize();
    return (field);
}
