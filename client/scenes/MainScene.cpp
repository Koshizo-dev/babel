#include "MainScene.hpp"
#include "ChatBoxScene.hpp"
#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"
#include <QObject>
#include <iostream>

using namespace babel;

MainScene::MainScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing LoggingScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_parent = std::shared_ptr<QWidget>(new QWidget(this->getSceneManager()->getWidget().get()));
    this->_parent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->_parent->setMinimumSize(1280, 720);

    this->_initLayouts();
    this->_placeLayouts();
    this->clear();
}

MainScene::~MainScene() {
    this->_contacts.reset();
    this->_search.reset();
    this->_user.reset();
    this->_leftSideLayout.reset();
    this->_rightSideLayout.reset();
    this->_parentLayout.reset();
}

std::string MainScene::getName() {
    return "Main menu";
}

void MainScene::display() {
    this->_user->display();
    this->_contacts->display();
    this->_search->display();

    this->_messages->display();
    this->_chatBox->display();
    
    this->_parent->show();
}

void MainScene::clear() {
    this->_user->clear();
    this->_contacts->clear();
    this->_search->clear();

    this->_messages->clear();
    this->_chatBox->clear();
    
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void MainScene::refresh() {
    this->_user->refresh();
    this->_contacts->refresh();
    this->_search->refresh();

    this->_messages->clear();
    this->_chatBox->clear();
    
    this->_parent->repaint();
}

std::shared_ptr<SceneManager> MainScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

void MainScene::_initLayouts() {
    this->_parentLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout(this->_parent.get()));

    this->_initLeftLayout();
    this->_initRightLayout();
}


void MainScene::_initLeftLayout() {
    this->_leftSideLayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout());

    this->_user = std::unique_ptr<UserScene>(new UserScene(this->_clientManager));
    this->_contacts = std::unique_ptr<ContactScene>(new ContactScene(this->_clientManager));
    this->_search = std::unique_ptr<SearchScene>(new SearchScene(this->_clientManager));
}

void MainScene::_initRightLayout() {
    this->_rightSideLayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout());

    this->_messages = std::unique_ptr<ChatScene>(new ChatScene(this->_clientManager));
    this->_chatBox = std::unique_ptr<ChatBoxScene>(new ChatBoxScene(this->_clientManager));
}

void MainScene::_placeLayouts() {
    this->_parentLayout->addLayout(this->_leftSideLayout.get(), 2);
    this->_parentLayout->addLayout(this->_rightSideLayout.get(), 5);

    this->_placeLeftLayout();
    this->_placeRightLayout();
}

void MainScene::_placeLeftLayout() {
    this->_user->getWidget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->_leftSideLayout->addWidget(this->_user->getWidget().get());
    this->_leftSideLayout->addLayout(this->_search->getLayout().get());
    this->_leftSideLayout->addWidget(this->_contacts->getWidget().get());
}

void MainScene::_placeRightLayout() {
    this->_rightSideLayout->addWidget(this->_messages->getWidget().get(), 12);
    this->_rightSideLayout->addLayout(this->_chatBox->getLayout().get(), 2);
}
