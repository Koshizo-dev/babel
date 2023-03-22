#include "ClientManager.hpp"
#include "displays/QDisplay.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

#include "../protocol/packets/LoginPacket.hpp"

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin);

using namespace babel;

int main(int argc, char **argv) {
    std::shared_ptr<ClientManager> clientManager = std::shared_ptr<ClientManager>(new ClientManager());

    clientManager->packetManager = std::make_shared<ClientPacketManager>((clientManager));
    LoginPacket packet("Koshizo");
    clientManager->packetManager->handlePacket(packet);

    clientManager->self = std::shared_ptr<Client>(new Client("Koshizo"));
    std::shared_ptr<Client> hyside(new Client("hyside"));
    std::shared_ptr<Client> rimost(new Client("rimost"));
    hyside->setChatting(true);
    hyside->setInCall(false);
    clientManager->self->setInCall(true);
    std::vector<std::shared_ptr<Message>> hysideMessages = {};
    std::vector<std::shared_ptr<Message>> rimostMessages = {};
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "SomeMessage", 1)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "AnotherMessage", 2)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "What", 3)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "Okay", 5)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "Go", 6)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "Yup!", 9)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(hyside, "Sheeeeeesh", 15)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "Why not", 4)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "Let's go bud", 7)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "It's been awesome", 8)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "Stop flooding plz", 16)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "a", 17)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "a", 18)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "a", 19)));
    hysideMessages.push_back(std::shared_ptr<Message>(new Message(clientManager->self, "a", 20)));
    rimostMessages.push_back(std::shared_ptr<Message>(new Message(rimost, "stfu", 4050013)));
    rimostMessages.push_back(std::shared_ptr<Message>(new Message(rimost, "wtf", 4053)));

    hyside->setMessages(hysideMessages);
    rimost->setMessages(rimostMessages);

    clientManager->clients.push_back(hyside);
    clientManager->clients.push_back(rimost);
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("nagi")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("rqndomhax")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("jebug")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("fosstodon")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("git")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("nixos")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("kurisu")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("uverworld")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("splitter")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("anilist")));
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("nginx")));
    DisplaySettings settings(argc, argv, "Babel | New Gen", 1280, 720);
    Display *display = new QDisplay(settings, clientManager);

    int code = display->run();

    delete display;
    return (code);
}
