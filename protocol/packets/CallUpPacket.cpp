#include "CallUpPacket.hpp"
#include "../fields/StringField.hpp"
#include "../fields/UnsignedIntegerField.hpp"
#include "../serialization/Serializer.hpp"

using namespace babel;

CallUpPacket::CallUpPacket(std::string username, unsigned int port) : CallUpPacket(username, "", port) {
}

CallUpPacket::CallUpPacket(std::string username, std::string hostname, unsigned int port) : _username(username), _hostname(hostname), _port(port) {
}

const std::string CallUpPacket::getUsername() const {
    return (this->_username);
}

const std::string CallUpPacket::getHostname() const {
    return (this->_hostname);
}

const unsigned int CallUpPacket::getPort() const {
    return (this->_port);
}

const PacketType CallUpPacket::getType() const {
    return (PacketType::CALL_UP);
}

const std::string CallUpPacket::serialize() const {
    Serializer serializer(this->getType());

    serializer << new StringField(this->_username);
    serializer << new StringField(this->_hostname);
    serializer << new UnsignedIntegerField(this->_port);
    return (serializer.serialize());
}

std::unique_ptr<Packet> CallUpPacket::deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const {
    if (packetFields.size() != 3)
        return (nullptr);

    std::unique_ptr<PacketField> field = std::move(packetFields[0]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *usernameField = static_cast<StringField*>(field.get());
    std::string username = usernameField->getValue();

    field = std::move(packetFields[1]);
    if (field->getType() != FieldType::STRING)
        return (nullptr);
    StringField *hostnameField = static_cast<StringField*>(field.get());
    std::string hostname = hostnameField->getValue();

    field = std::move(packetFields[2]);
    if (field->getType() != FieldType::UNSIGNED_INTEGER)
        return (nullptr);
    UnsignedIntegerField *portField = static_cast<UnsignedIntegerField*>(field.get());
    unsigned int port = portField->getValue();


    return (std::unique_ptr<Packet>(new CallUpPacket(username, hostname, port)));
}
