#include "ChatScene.hpp"
#include "../ClientError.hpp"

#include <QScrollBar>
#include <QTimer>
#include <iostream>

using namespace babel;

ChatScene::ChatScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ChatScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_chattingWith = this->_clientManager->getChatting();
    this->_scrollArea = new QScrollArea();
    this->_parent = new QWidget();
    this->_messagesLayout = new QVBoxLayout(this->_parent);
    this->_messagesLayout->addStretch();
}

ChatScene::~ChatScene() {
}

const std::string ChatScene::getName() const {
    return "Chat menu";
}

const void ChatScene::display() {
    this->_scrollArea->show();
    if (this->_chattingWith != nullptr)
        this->_parent->show();
}

const void ChatScene::clear() {
    this->_parent->hide();
    this->_scrollArea->hide();
}

const void ChatScene::refresh() {
    this->_parent->repaint();
    this->_scrollArea->repaint();
    // TODO refresh clients
}

const void ChatScene::handleEvent(Event &event) {
    switch (event.type) {
        case Event::NEW_CHATTING:
            {
                QWidget temp;
                this->_chattingWith = event.data.newChatting.newClient;
                for (auto *message: this->_messages) {
                    this->_messagesLayout->removeItem(message->getLayout());
                    QWidget().setLayout(message->getLayout());
                }
                this->_messages.clear();
                this->_initWidgets();
                this->_placeWidgets();
                this->display();
                QTimer::singleShot(100, [this]() {
                    QScrollBar *vScrollBar = _scrollArea->verticalScrollBar();
                    vScrollBar->setValue(vScrollBar->maximum());
                });
            }
            break;
        case Event::NEW_MESSAGE:
            {
                if (this->_chattingWith == nullptr)
                    return;
                auto newMessage = event.data.newMessage.message;
                if (newMessage->getAuthor()->getUsername() != this->_chattingWith->getUsername() && newMessage->getAuthor()->getUsername() != this->_clientManager->self->getUsername())
                    return;
                MessageBox *message = new MessageBox(newMessage->getAuthor(), {newMessage});

                this->_messages.push_back(message);
                this->_messagesLayout->addLayout(message->getLayout());
                QTimer::singleShot(5, [this]() {
                    QScrollBar *vScrollBar = _scrollArea->verticalScrollBar();
                    vScrollBar->setValue(vScrollBar->maximum());
                });
                // TODO group message and append it to the vector
            }
            break;
        default:
            break;
    }
}

const std::shared_ptr<SceneManager> ChatScene::getSceneManager() const {
    return (this->_clientManager->sceneManager);
}

QWidget *ChatScene::getWidget() {
    return (this->_scrollArea);
}

const void ChatScene::_initLayouts() {
}

const void ChatScene::_initWidgets() {
    auto groupedMessages = this->_groupMessagesByTime(this->_chattingWith);

    for (auto messages: groupedMessages) {
        std::shared_ptr<Client> client = messages[0]->getAuthor();
        MessageBox *message = new MessageBox(client, messages);
        this->_messages.push_back(message);
    }
}

const void ChatScene::_placeWidgets() {
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_scrollArea->setWidget(this->_parent);
    this->_scrollArea->setWidgetResizable(true);
    // this->_parent->setFixedWidth(700);
    this->_scrollArea->setFixedHeight(555);
    this->_messagesLayout->setSpacing(10);

    for (auto *message: this->_messages)
        this->_messagesLayout->addLayout(message->getLayout());
}

std::vector<std::vector<std::shared_ptr<Message>>> ChatScene::_groupMessagesByTime(std::shared_ptr<Client> client) {
    // combine the messages from both clients into a single vector
    std::vector<std::shared_ptr<Message>> allMessages = {};
    allMessages.reserve(client->getMessages().size());
    for (const auto message: client->getMessages())
        allMessages.emplace_back(message);

    // sort the messages by timestamp
    std::sort(allMessages.begin(), allMessages.end(),
              [](const std::shared_ptr<Message> a, const std::shared_ptr<Message> b) { return a->getTimestamp() < b->getTimestamp(); });

    // group the messages by time
    std::vector<std::vector<std::shared_ptr<Message>>> messages = {};
    std::shared_ptr<Message> lastMessage = nullptr;
    std::shared_ptr<Message> firstMessage = nullptr;
    for (const auto &message : allMessages) {
        if (messages.empty() || message->getAuthor() != lastMessage->getAuthor() || firstMessage->getTimestamp() - message->getTimestamp() + 5*1000*60 <= 0) {
            // create a new vector if this is the first message or if there's a time gap
            firstMessage = message;
            messages.emplace_back();
        }
        lastMessage = message;
        messages.back().push_back(message);
    }

    return (messages);
}