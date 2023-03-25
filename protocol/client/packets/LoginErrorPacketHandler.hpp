#pragma once

#include "../ClientPacketHandler.hpp"
#include "../../packets/LoginErrorPacket.hpp"

namespace babel {

    class LoginErrorPacketHandler: public ClientPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const override;
    };
    
}
