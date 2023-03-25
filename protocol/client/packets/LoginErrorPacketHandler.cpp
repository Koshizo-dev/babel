#include "LoginErrorPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/MainScene.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

const void LoginErrorPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const {
    try {
        LoginErrorPacket &loginPacket = dynamic_cast<LoginErrorPacket&>(packet);

        Event event(Event::LOGIN_FAILED);
        new (&event.data.loginFailed) Event::LoginFailed({loginPacket.getError()});
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
