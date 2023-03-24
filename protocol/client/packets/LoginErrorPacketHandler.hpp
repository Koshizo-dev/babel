#pragma once

#include "../ClientPacketHandler.hpp"
#include "../../packets/LoginErrorPacket.hpp"

namespace babel {

    class LoginErrorPacketHandler: public ClientPacketHandler {
        public:
            void handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) override;
    };
    
}
