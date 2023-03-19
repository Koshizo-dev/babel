#include "ClientManager.hpp"
#include "displays/QDisplay.hpp"
#include <QApplication>
#include <QPushButton>
#include <QFontDatabase>

#include <QtPlugin>

Q_IMPORT_PLUGIN(QXcbIntegrationPlugin);

using namespace babel;

int main(int argc, char **argv) {
    std::shared_ptr<ClientManager> clientManager = std::shared_ptr<ClientManager>(new ClientManager());
    clientManager->self = std::shared_ptr<Client>(new Client("Koshizo"));
    std::shared_ptr<Client> hyside(new Client("hyside"));
    hyside->setChatting(true);

    clientManager->clients.push_back(hyside);
    clientManager->clients.push_back(std::shared_ptr<Client>(new Client("rimost")));
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
