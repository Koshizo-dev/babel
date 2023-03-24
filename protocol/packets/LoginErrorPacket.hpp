#pragma once

#include "Packet.hpp"

namespace babel {

    class LoginErrorPacket: public Packet {
        public:
            LoginErrorPacket(std::string error = "");

            std::string getError();

            PacketType getType() override;
            std::string serialize() override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) override;

        private:
            std::string _error = "";
    };

}

