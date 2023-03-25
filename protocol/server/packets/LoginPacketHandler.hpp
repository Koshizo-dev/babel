#pragma once

#include "../ServerPacketHandler.hpp"
#include "../../packets/LoginPacket.hpp"

namespace babel {

    class LoginPacketHandler: public ServerPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const override;

        private:
            const std::string _trim(const std::string &s) const;
            const bool _containsChar(const std::string &str, char ch) const;
    };
    
}
