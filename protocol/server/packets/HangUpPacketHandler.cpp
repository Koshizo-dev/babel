#include "HangUpPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/HangUpPacket.hpp"

#include <typeinfo>

using namespace babel;

const void HangUpPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const {
    try {
        HangUpPacket &hangUpPacket = dynamic_cast<HangUpPacket&>(packet);

        serverManager->hangUp(origin, hangUpPacket.getUsername());
    } catch (std::bad_cast) {}
}
