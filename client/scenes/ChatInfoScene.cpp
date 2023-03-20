#include "ChatInfoScene.hpp"
#include "../ClientError.hpp"
#include "LoggingScene.hpp"
#include <iostream>

using namespace babel;

ChatInfoScene::ChatInfoScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ChatInfoScene::~ChatInfoScene() {
    this->_userLabel.reset();
    this->_callUpButton.reset();
    this->_hangUpButton.reset();
    this->_userLayout.reset();
    this->_parent.reset();
}

std::string ChatInfoScene::getName() {
    return "User menu";
}

void ChatInfoScene::display() {
    this->_parent->show();
}

void ChatInfoScene::clear() {
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void ChatInfoScene::refresh() {
    if (this->_clientManager->self->isInCall()) {
        this->_callUpButton->hide();
        this->_hangUpButton->show();
    } else {
        this->_callUpButton->show();
        this->_hangUpButton->hide();
    }
    this->_parent->repaint();
    // TODO refresh clients
}

std::shared_ptr<SceneManager> ChatInfoScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

std::shared_ptr<QWidget> ChatInfoScene::getWidget() {
    return (this->_parent);
}

void ChatInfoScene::_initLayouts() {
    this->_userLayout = std::unique_ptr<QHBoxLayout>(new QHBoxLayout(this->_parent.get()));
}

void ChatInfoScene::_initWidgets() {
    this->_parent = std::shared_ptr<QWidget>(new QWidget());
    this->_userLabel = std::unique_ptr<QLabel>(new QLabel(this->_clientManager->getChatting()->getUsername().c_str()));

    this->_callUpButton = std::unique_ptr<QToolButton>(new QToolButton());
    this->_callUpButton->setIcon(QIcon("assets/call-up.png"));
    this->_hangUpButton = std::unique_ptr<QToolButton>(new QToolButton());
    this->_hangUpButton->setIcon(QIcon("assets/hang-up.png"));

    QObject::connect(this->_callUpButton.get(), &QToolButton::clicked, [=]() {
        // TODO leave all server side
        this->_clientManager->self->setInCall(true);
        this->refresh();
        printf("Joined call!\n");
    });

    QObject::connect(this->_hangUpButton.get(), &QToolButton::clicked, [=]() {
        // TODO leave all server side
        this->_clientManager->self->setInCall(false);
        this->refresh();
        printf("Left call!\n");
    });

}

void ChatInfoScene::_placeWidgets() {
    this->_userLabel->setStyleSheet("font-style: italic; font-weight: 900; text-decoration: underline;");
    this->_userLayout->addWidget(this->_userLabel.get());

    this->_callUpButton->setIconSize(QSize(64, 64));
    this->_callUpButton->setFixedSize(64, 64);
    this->_callUpButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");

    this->_hangUpButton->setIconSize(QSize(64, 64));
    this->_hangUpButton->setFixedSize(64, 64);
    this->_hangUpButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    this->_userLayout->addWidget(this->_hangUpButton.get());
    this->_userLayout->addWidget(this->_callUpButton.get());
    this->_hangUpButton->hide();
}
