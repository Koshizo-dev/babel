#pragma once

#include "../ClientPacketHandler.hpp"

namespace babel {

    class ContactPacketHandler: public ClientPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const override;
    };
    
}
