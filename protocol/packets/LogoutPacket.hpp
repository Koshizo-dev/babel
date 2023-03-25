#pragma once

#include "Packet.hpp"

namespace babel {

    class LogoutPacket: public Packet {
        public:
            LogoutPacket();

            PacketType getType() override;
            std::string serialize() override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) override;

        private:
    };

}

