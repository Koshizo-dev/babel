#pragma once

#include "../ClientPacketHandler.hpp"

namespace babel {

    class LogoutPacketHandler: public ClientPacketHandler {
        public:
            void handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) override;
    };
    
}
