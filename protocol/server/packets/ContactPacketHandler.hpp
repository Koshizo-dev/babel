#pragma once

#include "../ServerPacketHandler.hpp"

namespace babel {

    class ContactPacketHandler: public ServerPacketHandler {
        public:
            const void handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const override;

        private:
            const std::string _trim(const std::string &target) const;
    };
    
}
