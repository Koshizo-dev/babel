#pragma once

#include "Packet.hpp"

namespace babel {

    class MessagePacket: public Packet {
        public:
            MessagePacket() {}
            MessagePacket(std::string recipient, std::string content);
            MessagePacket(std::string sender, std::string recipient, std::string content, std::uint64_t timestamp);

            std::string getSender();
            std::string getRecipient();
            std::string getContent();
            std::uint64_t getTimestamp();

            PacketType getType() override;
            std::string serialize() override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) override;

        private:
            std::string _sender = "";
            std::string _recipient = "";
            std::string _content = "";
            std::uint64_t _timestamp = 0;
    };

}

