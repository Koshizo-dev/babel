#pragma once

#include "Packet.hpp"

namespace babel {

    class LoginErrorPacket: public Packet {
        public:
            LoginErrorPacket(std::string error = "");

            const std::string getError() const;

            const PacketType getType() const override;
            const std::string serialize() const override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const override;

        private:
            const std::string _error;
    };

}

