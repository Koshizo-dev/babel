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
    DisplaySettings settings(argc, argv, "Babel | New Gen", 1280, 720);
    Display *display = new QDisplay(settings, clientManager);

    int code = display->run();

    delete display;
    return (code);
}
