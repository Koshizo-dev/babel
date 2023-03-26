#pragma once

#include "Packet.hpp"

namespace babel {

    class LogoutPacket: public Packet {
        public:
            LogoutPacket();

            const PacketType getType() const override;
            const std::string serialize() const override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const override;

        private:
    };

}

