#include "HangUpPacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/Scene.hpp"
#include "../../packets/HangUpPacket.hpp"

#include <typeinfo>

using namespace babel;

const void HangUpPacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) const {
    try {
        HangUpPacket &hangUpPacket = dynamic_cast<HangUpPacket&>(packet);

        std::shared_ptr<Client> target = nullptr;
        std::cout << "received close !" << std::endl;

        if (hangUpPacket.getUsername() == clientManager->self->getUsername()) {
            target = clientManager->self;
            clientManager->stopAudioSocket();
        }
        else {
            target = clientManager->getClient(hangUpPacket.getUsername());
            if (target == nullptr)
                return;
            clientManager->audioSettings->setReceiver(AudioReceiver("", 0));
        }

        target->hangUp();

        Event event(Event::CALL_STATE_UPDATE);
        new (&event.data.callStateUpdate) Event::CallStateUpdate({target});
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
