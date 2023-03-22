#pragma once

#include "../ClientPacketHandler.hpp"
#include "../../packets/LoginPacket.hpp"

namespace babel {

    class LoginPacketHandler: public ClientPacketHandler {
        public:
            void handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) override;
    };
    
}
