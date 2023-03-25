#include "MessagePacketHandler.hpp"
#include "../../../client/ClientManager.hpp"
#include "../../../client/scenes/Scene.hpp"
#include "../../../client/Message.hpp"
#include "../../packets/MessagePacket.hpp"

#include <iostream>
#include <typeinfo>

using namespace babel;

void MessagePacketHandler::handle(Packet &packet, std::shared_ptr<ClientManager> clientManager) {
    try {
        MessagePacket &messagePacket = dynamic_cast<MessagePacket&>(packet);

        std::shared_ptr<Client> discussion = nullptr;
        std::shared_ptr<Client> author = nullptr;
        if (clientManager->self->getUsername() == messagePacket.getSender()) {
            discussion = clientManager->getClient(messagePacket.getRecipient());
            author = clientManager->self;
        }
        else {
            std::shared_ptr<Client> tmp = clientManager->getClient(messagePacket.getSender());
            discussion = author;
            author = tmp;
        }

        std::shared_ptr<Message> message = std::make_shared<Message>(author, messagePacket.getContent(), messagePacket.getTimestamp(), true);
        author->addMessage(message);
        Event event(Event::NEW_MESSAGE);
        new (&event.data.newMessage) Event::NewMessage({message});
        clientManager->sceneManager->getScene()->handleEvent(event);
    } catch (std::bad_cast) {}
}
