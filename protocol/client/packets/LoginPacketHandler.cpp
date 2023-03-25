#include "LoginPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/MainScene.hpp"

#include <typeinfo>

using namespace babel;

const void LoginPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const {
    try {
        LoginPacket &loginPacket = dynamic_cast<LoginPacket&>(packet);

        clientManager->self = std::shared_ptr<Client>(new Client(loginPacket.getUsername()));
        clientManager->sceneManager->setScene(new MainScene(clientManager));
    } catch (std::bad_cast) {}
}
