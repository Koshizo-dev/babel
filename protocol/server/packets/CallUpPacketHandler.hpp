#pragma once

#include "../ServerPacketHandler.hpp"

namespace babel {

    class CallUpPacketHandler: public ServerPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const override;
    };
    
}
