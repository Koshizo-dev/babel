#include "QDisplay.hpp"
#include "../scenes/SceneManager.hpp"
#include "../scenes/MainScene.hpp"
#include "../scenes/LoggingScene.hpp"
#include "../scenes/Scene.hpp"
#include "../entities/Window.hpp"

#include <QPushButton>
#include <QFontDatabase>

using namespace babel;

QDisplay::QDisplay(DisplaySettings settings, std::shared_ptr<ClientManager> clientManager) : _settings(settings), _clientManager(clientManager){
    this->_app = std::make_unique<QApplication>(settings.argc, settings.argv);
    this->_app->setApplicationDisplayName(this->_settings.title.c_str());
    this->_window = std::make_shared<Window>(clientManager);
    this->_loadFont();
    this->_clientManager->sceneManager = std::make_shared<SceneManager>(this->_window);
    this->_clientManager->sceneManager->setScene(new LoggingScene(this->_clientManager));

    _window->show();
}

QDisplay::~QDisplay() {
    this->_app->closeAllWindows();
}

int QDisplay::run() {
    return this->_app->exec();
}

void QDisplay::_loadFont() {
    // Load the font file
    QFontDatabase::addApplicationFont("assets/Vesta-Pro-Regular.ttf");

    // Set the loaded font as the default font for the application
    QFont font("Vesta-Pro-Regular", 18);
    this->_app->setFont(font);
}
