#pragma once

#include "Packet.hpp"

namespace babel {

    class ContactPacket: public Packet {
        public:
            ContactPacket() {}
            ContactPacket(std::string username);

            std::string getUsername();

            PacketType getType() override;
            std::string serialize() override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) override;

        private:
            std::string _username = "";
    };

}

