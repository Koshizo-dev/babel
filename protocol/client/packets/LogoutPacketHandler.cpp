#include "LogoutPacketHandler.hpp"
#include "../../packets/LogoutPacket.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/Event.hpp"
#include "../../../client/scenes/Scene.hpp"

using namespace babel;

void LogoutPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        LogoutPacket &logoutPacket = dynamic_cast<LogoutPacket&>(packet);
        clientManager->disconnect();
        Event event(Event::LOGOUT);
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
