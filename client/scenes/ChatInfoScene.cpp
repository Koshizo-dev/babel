#include "ChatInfoScene.hpp"
#include "../ClientError.hpp"
#include "LoggingScene.hpp"
#include <iostream>

using namespace babel;

ChatInfoScene::ChatInfoScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_chattingWith = clientManager->getChatting();
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ChatInfoScene::~ChatInfoScene() {
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

void ChatInfoScene::refresh() {
    this->_parent->repaint();
}

void ChatInfoScene::handleEvent(Event &event) {
    if (event.type != Event::CALL_STATE_UPDATE && event.type != Event::NEW_CHATTING)
        return;

    if (event.type == Event::NEW_CHATTING) {
        this->_chattingWith = event.data.newChatting.newClient;
        this->_userLabel->setText(this->_chattingWith->getUsername().c_str());
    } else
        this->_clientManager->self->setInCall(!this->_clientManager->self->isInCall());

    if (this->_clientManager->self->isInCall()) {
        this->_callUpButton->hide();
        this->_callUpAbsentButton->hide();
        if (this->_chattingWith->isInCall()) {
            this->_hangUpAbsentButton->hide();
            this->_hangUpButton->show();
        }
        else {
            this->_hangUpButton->hide();
            this->_hangUpAbsentButton->show();
        }
    } else {
        this->_hangUpButton->hide();
        this->_hangUpAbsentButton->hide();
        if (this->_chattingWith->isInCall()) {
            this->_callUpAbsentButton->hide();
            this->_callUpButton->show();
        }
        else {
            this->_callUpButton->hide();
            this->_callUpAbsentButton->show();
        }
    }
}

std::shared_ptr<SceneManager> ChatInfoScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

QWidget *ChatInfoScene::getWidget() {
    return (this->_parent);
}

void ChatInfoScene::_initLayouts() {
    this->_userLayout = new QHBoxLayout(this->_parent);
}

void ChatInfoScene::_initWidgets() {
    this->_parent = new QWidget();
    this->_userLabel = new QLabel(this->_clientManager->getChatting()->getUsername().c_str());

    this->_callUpButton = new QToolButton();
    this->_callUpButton->setIcon(QIcon("assets/call-up.png"));
    this->_hangUpButton = new QToolButton();
    this->_hangUpButton->setIcon(QIcon("assets/hang-up.png"));
    this->_callUpAbsentButton = new QToolButton();
    this->_callUpAbsentButton->setIcon(QIcon("assets/call-up_absent.png"));
    this->_hangUpAbsentButton = new QToolButton();
    this->_hangUpAbsentButton->setIcon(QIcon("assets/hang-up_absent.png"));
}

void ChatInfoScene::_placeWidgets() {
    this->_userLabel->setStyleSheet("font-style: italic; font-weight: 900; text-decoration: underline;");
    this->_userLayout->addWidget(this->_userLabel);

    this->_callUpButton->setIconSize(QSize(64, 64));
    this->_callUpButton->setFixedSize(64, 64);
    this->_callUpButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    this->_callUpAbsentButton->setIconSize(QSize(64, 64));
    this->_callUpAbsentButton->setFixedSize(64, 64);
    this->_callUpAbsentButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");

    this->_hangUpButton->setIconSize(QSize(64, 64));
    this->_hangUpButton->setFixedSize(64, 64);
    this->_hangUpButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    this->_hangUpAbsentButton->setIconSize(QSize(64, 64));
    this->_hangUpAbsentButton->setFixedSize(64, 64);
    this->_hangUpAbsentButton->setStyleSheet("background-color: rgba(0, 0, 0, 0); border: none;");
    this->_userLayout->addWidget(this->_callUpButton);
    this->_userLayout->addWidget(this->_callUpAbsentButton);
    this->_userLayout->addWidget(this->_hangUpButton);
    this->_userLayout->addWidget(this->_hangUpAbsentButton);
    this->refresh();

    QObject::connect(this->_callUpButton, &QToolButton::clicked, [=]() {
        this->_callUp();
    });

    QObject::connect(this->_callUpAbsentButton, &QToolButton::clicked, [=]() {
        this->_callUp();
    });

    QObject::connect(this->_hangUpButton, &QToolButton::clicked, [=]() {
        this->_hangUp();
    });

    QObject::connect(this->_hangUpAbsentButton, &QToolButton::clicked, [=]() {
        this->_hangUp();
    });
}

void ChatInfoScene::_callUp() {
    // TODO leave all server side
    this->_clientManager->self->setInCall(true);
    printf("Joined call!\n");
}

void ChatInfoScene::_hangUp() {
    // TODO leave all server side
    this->_clientManager->self->setInCall(false);
    printf("Left call!\n");
}
