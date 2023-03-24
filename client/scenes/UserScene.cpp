#include "UserScene.hpp"
#include "../ClientError.hpp"
#include "LoggingScene.hpp"
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

QWidget *UserScene::getWidget() {
    return (this->_parent);
}

void UserScene::_initLayouts() {
    this->_userLayout = new QHBoxLayout(this->_parent);
}

void UserScene::_initWidgets() {
    this->_parent = new QWidget();
    this->_userLabel = new QLabel(this->_clientManager->self->getUsername().c_str());

    this->_logoutButton = new QToolButton();
    this->_logoutButton->setIcon(QIcon("assets/logout.png"));

    QObject::connect(this->_logoutButton, &QToolButton::clicked, [=]() {
        // TODO disconnect user server side
        this->_clientManager->disconnect();
        printf("User disconnected!\n");
        this->getSceneManager()->setScene(new LoggingScene(this->_clientManager));
    });
    
}

void UserScene::_placeWidgets() {
    this->_userLayout->addWidget(this->_clientManager->self->getIcon());
    this->_userLayout->addWidget(this->_userLabel);

    this->_logoutButton->setIconSize(QSize(64, 64));
    this->_logoutButton->setFixedSize(64, 64);
    this->_logoutButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    this->_userLayout->addWidget(this->_logoutButton);
}
