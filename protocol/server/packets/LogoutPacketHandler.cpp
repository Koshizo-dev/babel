#include "LogoutPacketHandler.hpp"
#include "../../packets/LogoutPacket.hpp"
#include "../../../server/ServerManager.hpp"

using namespace babel;

const void LogoutPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) const {
    try {
        LogoutPacket &logoutPacket = dynamic_cast<LogoutPacket&>(packet);
        serverManager->logout(origin);
    } catch (std::bad_cast) {}
}
