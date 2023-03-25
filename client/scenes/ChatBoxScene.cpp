#include "ChatBoxScene.hpp"
#include "SearchScene.hpp"
#include "../ClientError.hpp"
#include <iostream>

using namespace babel;

ChatBoxScene::ChatBoxScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing SearchScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initLayouts();
}

ChatBoxScene::~ChatBoxScene() {
}

const std::string ChatBoxScene::getName() const {
    return "ChatBox menu";
}

const void ChatBoxScene::display() {
    if (this->_clientManager->getChatting() != nullptr)
        this->_chatBoxInput->show();
}

const void ChatBoxScene::clear() {
}

const void ChatBoxScene::refresh() {
}

const void ChatBoxScene::handleEvent(Event &event) {
    if (event.type != Event::NEW_CHATTING)
        return;
    if (event.data.newChatting.previousClient == nullptr) {
        this->_initWidgets();
        this->_placeWidgets();
    } else {
        auto newChatting = event.data.newChatting.newClient;
        this->_chatBoxInput->setPlaceholderText((std::string("Message @") + newChatting->getUsername()));
    }
}

const std::shared_ptr<SceneManager> ChatBoxScene::getSceneManager() const {
    return (this->_clientManager->sceneManager);
}

QLayout *ChatBoxScene::getLayout() {
    return (this->_chatBoxLayout);
}

void ChatBoxScene::_initLayouts() {
    this->_chatBoxLayout = new QHBoxLayout();
}

void ChatBoxScene::_initWidgets() {
    this->_chatBoxInput = new ChatBox((std::string("Message @") + this->_clientManager->getChatting()->getUsername()), this->_clientManager);
}

void ChatBoxScene::_placeWidgets() {
    this->_chatBoxLayout->addWidget(this->_chatBoxInput);
}
