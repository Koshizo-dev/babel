#pragma once

#include "../Packet.hpp"

namespace babel {

    class LoginPacket: public Packet {
        public:
            LoginPacket(std::string username);

            std::string getUsername();

            PacketType getType() override;
            std::string serialize() override;
            std::unique_ptr<Packet> deserialize(std::string &packet) override;

        private:
            std::string _username;
    };

}

