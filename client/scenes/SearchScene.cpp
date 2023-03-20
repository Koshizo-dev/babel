#include "SearchScene.hpp"
#include "../ClientError.hpp"
#include <iostream>

using namespace babel;

SearchScene::SearchScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing SearchScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

SearchScene::~SearchScene() {
    this->_searchInput.reset();
}

std::string SearchScene::getName() {
    return "Search menu";
}

void SearchScene::display() {
}

void SearchScene::clear() {
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void SearchScene::refresh() {
}

std::shared_ptr<SceneManager> SearchScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

std::shared_ptr<QLayout> SearchScene::getLayout() {
    return (this->_searchLayout);
}

void SearchScene::_initLayouts() {
    this->_searchLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
}

void SearchScene::_initWidgets() {
    this->_searchInput = std::unique_ptr<QLineEdit>(new QLineEdit());

    QObject::connect(this->_searchInput.get(), &QLineEdit::returnPressed, [=]() {
        // TODO If user does exist, switch up to his conversation, otherwise add a new contact at the top of the list but don't switch to it
        std::cout << "Pressed returned ! | text = [" << this->_searchInput->text().toStdString() << "]" << std::endl;
    });
}

void SearchScene::_placeWidgets() {
    this->_searchLayout->addWidget(this->_searchInput.get());
    this->_searchInput->setPlaceholderText("Find an user.");
}
