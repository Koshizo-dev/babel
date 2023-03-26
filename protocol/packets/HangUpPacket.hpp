#pragma once

#include "Packet.hpp"

namespace babel {

    class HangUpPacket: public Packet {
        public:
            HangUpPacket(std::string username = "");

            const std::string getUsername() const;

            const PacketType getType() const override;
            const std::string serialize() const override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const override;

        private:
            const std::string _username;
    };

}

