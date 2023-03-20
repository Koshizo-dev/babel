#include "UserScene.hpp"
#include "../ClientError.hpp"
#include <iostream>

using namespace babel;

UserScene::UserScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

UserScene::~UserScene() {
}

std::string UserScene::getName() {
    return "User menu";
}

void UserScene::display() {
    this->_parent->show();
}

void UserScene::clear() {
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void UserScene::refresh() {
    this->_parent->repaint();
    // TODO refresh clients
}

std::shared_ptr<SceneManager> UserScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

std::shared_ptr<QWidget> UserScene::getWidget() {
    return (this->_parent);
}

void UserScene::_initLayouts() {
    this->_userLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout(this->_parent.get()));
}

void UserScene::_initWidgets() {
    this->_parent = std::shared_ptr<QWidget>(new QWidget());
    this->_userLabel = std::unique_ptr<QLabel>(new QLabel(this->_clientManager->self->getUsername().c_str()));
}

void UserScene::_placeWidgets() {
    this->_userLayout->addWidget(this->_clientManager->self->getIcon().get());
    this->_userLayout->addWidget(this->_userLabel.get());
}
