#include "QDisplay.hpp"
#include "../scenes/SceneManager.hpp"
#include "../scenes/MainScene.hpp"
#include "../scenes/LoggingScene.hpp"
#include "../scenes/Scene.hpp"

#include <QPushButton>
#include <QFontDatabase>

using namespace babel;

QDisplay::QDisplay(int argc, char **argv, std::string name, int width, int height) {
    this->_name = name;
    this->_app = std::unique_ptr<QApplication>(new QApplication(argc, argv));
    this->_app->setApplicationDisplayName(name.c_str());
    this->_window = std::shared_ptr<QWidget>(new QWidget);
    this->_window->setGeometry(0, 0, 1280, 720);
    this->_loadFont();

    this->_sceneManager = std::shared_ptr<SceneManager>(new SceneManager(this->_window));

    this->_sceneManager->setScene(new LoggingScene(this->_sceneManager));
    // this->_sceneManager->setScene(new MainScene(this->_sceneManager));

    _window->show();
}

QDisplay::~QDisplay() {
    this->_app.reset();
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
