#include "CallUpPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/Scene.hpp"
#include "../../packets/CallUpPacket.hpp"

#include <typeinfo>

using namespace babel;

const void CallUpPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const {
    try {
        CallUpPacket &callUpPacket = dynamic_cast<CallUpPacket&>(packet);

        std::shared_ptr<Client> target = nullptr;

        if (callUpPacket.getUsername() == clientManager->self->getUsername()) {
            target = clientManager->self;
            clientManager->startAudioSocket();
        }
        else
            target = clientManager->getClient(callUpPacket.getUsername());
        if (target == nullptr)
            return;

        target->callUp(callUpPacket.getHostname(), callUpPacket.getPort());

        Event event(Event::CALL_STATE_UPDATE);
        new (&event.data.callStateUpdate) Event::CallStateUpdate({target});
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
