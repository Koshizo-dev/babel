#include "ChatInfoScene.hpp"
#include "../ClientError.hpp"
#include "LoggingScene.hpp"
#include "../../protocol/packets/CallUpPacket.hpp"
#include "../../protocol/packets/HangUpPacket.hpp"

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

const std::string ChatInfoScene::getName() const {
    return "ChatInfo menu";
}

const void ChatInfoScene::display() {
    if (this->_chattingWith != nullptr)
        this->_parent->show();
}

const void ChatInfoScene::clear() {
    this->_parent->hide();
}

const void ChatInfoScene::refresh() {
    this->_parent->repaint();
}

const void ChatInfoScene::handleEvent(Event &event) {
    if (event.type != Event::CALL_STATE_UPDATE && event.type != Event::NEW_CHATTING)
        return;

    if (event.type == Event::NEW_CHATTING) {
        this->_chattingWith = event.data.newChatting.newClient;
        this->_userLabel->setText(this->_chattingWith->getUsername().c_str());
        if (event.newChatting.previousClient == nullptr)
            this->display();
    }

    this->_updateCallLayout();
}

const std::shared_ptr<SceneManager> ChatInfoScene::getSceneManager() const {
    return (this->_clientManager->sceneManager);
}

QWidget *ChatInfoScene::getWidget() {
    return (this->_parent);
}

const void ChatInfoScene::_initLayouts() {
    this->_userLayout = new QHBoxLayout(this->_parent);
}

const void ChatInfoScene::_initWidgets() {
    this->_userLabel = new QLabel();
    this->_parent = new QWidget();

    this->_callUpButton = new QToolButton();
    this->_callUpButton->setIcon(QIcon("assets/call-up.png"));
    this->_hangUpButton = new QToolButton();
    this->_hangUpButton->setIcon(QIcon("assets/hang-up.png"));
    this->_callUpAbsentButton = new QToolButton();
    this->_callUpAbsentButton->setIcon(QIcon("assets/call-up_absent.png"));
    this->_hangUpAbsentButton = new QToolButton();
    this->_hangUpAbsentButton->setIcon(QIcon("assets/hang-up_absent.png"));
}

const void ChatInfoScene::_placeWidgets() {
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
    this->_parent->setLayout(this->_userLayout);

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

const void ChatInfoScene::_updateCallLayout() {
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

const void ChatInfoScene::_callUp() {
    CallUpPacket callUp(this->_chattingWith->getUsername(), this->_clientManager->audioSocket->getPort());
    this->_clientManager->transporter->sendMessage(callUp.serialize());
}

const void ChatInfoScene::_hangUp() {
    HangUpPacket hangUp(this->_chattingWith->getUsername());
    this->_clientManager->transporter->sendMessage(hangUp.serialize());
}
