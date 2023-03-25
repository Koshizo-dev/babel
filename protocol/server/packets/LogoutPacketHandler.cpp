#include "LogoutPacketHandler.hpp"
#include "../../packets/LogoutPacket.hpp"
#include "../../../server/ServerManager.hpp"

using namespace babel;

void LogoutPacketHandler::handle(Packet &packet, std::shared_ptr<ServerManager> serverManager, IoClient *origin) {
    try {
        LogoutPacket &logoutPacket = dynamic_cast<LogoutPacket&>(packet);
        serverManager->logout(origin);
    } catch (std::bad_cast) {}
}
