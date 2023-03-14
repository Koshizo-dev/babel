#include "QDisplay.hpp"
#include "../scenes/MainScene.hpp"
#include "../scenes/Scene.hpp"
#include <QPushButton>
#include <QFontDatabase>

using namespace babel;

QDisplay::QDisplay(int argc, char **argv, std::string name, int width, int height) {
    this->_name = name;
    this->_app = new QApplication(argc, argv);
    this->_app->setApplicationDisplayName(name.c_str());
    this->_window = new QWidget;
    this->_window->setGeometry(0, 0, 1280, 720);
    this->_loadFont();

    Scene *scene = new MainScene();
    scene->load(std::shared_ptr<QWidget>(this->_window));
    scene->display();
    
    _window->show();
}

// int Display::centerX(int widgetWidth) {
//     return ((this->_window->width() - widgetWidth) / 2);
// }

// int Display::centerY(int widgetHeight) {
//     return ((this->_window->height() - widgetHeight) / 2);
// }

QDisplay::~QDisplay() {
    if (this->_window) 
        delete this->_window;
    
    if (this->_app)
        delete this->_app;
}

int QDisplay::run() {
    return this->_app->exec();
}

void QDisplay::_loadFont() {
    // Load the font file
    QFontDatabase::addApplicationFont("assets/Vesta-Pro-Regular.ttf");

    // Set the loaded font as the default font for the application
    QFont font("Vesta-Pro-Regular", 12);
    this->_app->setFont(font);
}
