#pragma once

#include "Packet.hpp"

namespace babel {

    class MessagePacket: public Packet {
        public:
            MessagePacket(): _sender(""), _recipient(""), _content(""), _timestamp(0) {}

            MessagePacket(std::string recipient, std::string content);
            MessagePacket(std::string sender, std::string recipient, std::string content, std::uint64_t timestamp);

            const std::string getSender() const;
            const std::string getRecipient() const;
            const std::string getContent() const;
            const std::uint64_t getTimestamp() const;

            const PacketType getType() const override;
            const std::string serialize() const override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const override;

        private:
            const std::string _sender;
            const std::string _recipient;
            const std::string _content;
            const std::uint64_t _timestamp;
    };

}

