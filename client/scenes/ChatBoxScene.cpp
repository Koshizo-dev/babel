#include "ChatBoxScene.hpp"
#include "SearchScene.hpp"
#include "../ClientError.hpp"
#include <iostream>

using namespace babel;

ChatBoxScene::ChatBoxScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing SearchScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ChatBoxScene::~ChatBoxScene() {
    this->_chatBoxInput.reset();
    // this->_searchLayout.reset();
}

std::string ChatBoxScene::getName() {
    return "ChatBox menu";
}

void ChatBoxScene::display() {
}

void ChatBoxScene::clear() {
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void ChatBoxScene::refresh() {
}

std::shared_ptr<SceneManager> ChatBoxScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

std::shared_ptr<QLayout> ChatBoxScene::getLayout() {
    return (this->_chatBoxLayout);
}

void ChatBoxScene::_initLayouts() {
    this->_chatBoxLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
}

void ChatBoxScene::_initWidgets() {
    this->_chatBoxInput = std::unique_ptr<ChatBox>(new ChatBox((std::string("Message ") + this->_clientManager->getChatting()->getUsername())));
}

void ChatBoxScene::_placeWidgets() {
    this->_chatBoxLayout->addWidget(this->_chatBoxInput.get());
}
