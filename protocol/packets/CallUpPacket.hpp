#pragma once

#include "Packet.hpp"

namespace babel {

    class CallUpPacket: public Packet {
        public:
            CallUpPacket(): _username(""), _hostname(""), _port(0) {}
            CallUpPacket(std::string username, unsigned int port);
            CallUpPacket(std::string username, std::string hostname, unsigned int port);

            const std::string getUsername() const;
            const std::string getHostname() const;
            const unsigned int getPort() const;

            const PacketType getType() const override;
            const std::string serialize() const override;
            std::unique_ptr<Packet> deserialize(std::vector<std::unique_ptr<PacketField>> packetFields) const override;

        private:
            const std::string _username;
            const std::string _hostname;
            const unsigned int _port;
    };

}

