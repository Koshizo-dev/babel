#pragma once

#include "../ServerPacketHandler.hpp"
#include "../../packets/LoginPacket.hpp"

namespace babel {

    class LogoutPacketHandler: public ServerPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const override;
    };
    
}
