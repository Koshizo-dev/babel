#include "CallUpPacketHandler.hpp"
#include "../../../server/ServerManager.hpp"
#include "../../packets/CallUpPacket.hpp"

#include <typeinfo>

using namespace babel;

const void CallUpPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const {
    try {
        CallUpPacket &callUpPacket = dynamic_cast<CallUpPacket&>(packet);

        serverManager->callUp(origin, callUpPacket.getUsername(), callUpPacket.getPort());
    } catch (std::bad_cast) {}
}
