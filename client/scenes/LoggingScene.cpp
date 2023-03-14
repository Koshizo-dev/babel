#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"

#include <qobject.h>
#include <iostream>

using namespace babel;

LoggingScene::~LoggingScene() {
    this->_loggingButton.reset();
}

std::string LoggingScene::getName() {
    return "Logging menu";
}

// Load the Scene with the parent passed as parameter
// If function already loaded
//     Will call the Scene::clear.
//     Will override the current parent.
void LoggingScene::load(std::shared_ptr<QWidget> parent) {
    if (this->_parent)
        this->clear();
    this->_parent = parent;
}

void LoggingScene::display() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");

    this->_loggingButton = std::unique_ptr<QPushButton>(new QPushButton("Login", this->_parent.get()));
    this->_loggingButton->setGeometry(0, 0, 200, 100);

    int x = centerX(this->_parent.get(), this->_loggingButton->width());
    int y = centerY(this->_parent.get(), this->_loggingButton->height());
    this->_loggingButton->move(x, y);


    QObject::connect(this->_loggingButton.get(), &QPushButton::clicked, [=]() {
       this->_loggingButtonClicked(); 
    });
}

void LoggingScene::_loggingButtonClicked() {
    if (this->_loggingAction) {
        return;
    }
    this->_loggingAction = true;
    std::cerr << "[DEBUG] Sending request to connect to server" << std::endl;
    // TODO Connection packet to server
}

void LoggingScene::clear() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void LoggingScene::refresh() {
    if (this->_parent == nullptr)
        throw ClientError("LoggingScene needs to be loaded first!");
}
