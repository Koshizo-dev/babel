#pragma once

#include "../ServerPacketHandler.hpp"

namespace babel {

    class MessagePacketHandler: public ServerPacketHandler {
        public:
            void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) override;

        private:
            std::string _trim(const std::string &target);
    };
    
}
