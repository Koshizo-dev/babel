#include "PacketManager.hpp"
#include "fields/CharacterField.hpp"
#include "serialization/Deserializer.hpp"

using namespace babel;

std::unique_ptr<Packet> PacketManager::deserialize(std::string &packet) {
    char const *data = packet.data();
    Deserializer deserializer;
    int index = 0;

    CharacterField magic = CharacterField::deserialize(data);
    index += magic.getSize();
    if (magic.getValue() != 0x32)
        return (nullptr);

    CharacterField packetType = CharacterField::deserialize(&data[index]);
    index += packetType.getSize();

    std::vector<std::unique_ptr<PacketField>> fields = {};
    std::unique_ptr<PacketField> nextField = nullptr;

    while ((nextField = deserializer.nextField(&data[index], &index)) != nullptr)
        fields.push_back(std::move(nextField));

    return (deserializer.deserialize(static_cast<PacketType>(packetType.getValue()), std::move(fields)));
}

std::string PacketManager::serialize(Packet &packet) {
    return packet.serialize();
}
