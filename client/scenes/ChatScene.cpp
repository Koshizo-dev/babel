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
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ChatScene::~ChatScene() {
}

std::string ChatScene::getName() {
    return "Chat menu";
}

void ChatScene::display() {
    this->_parent->show();
    this->_scrollArea->show();
}

void ChatScene::clear() {
    this->_parent->hide();
    this->_scrollArea->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void ChatScene::refresh() {
    this->_parent->repaint();
    // TODO refresh clients
}

void ChatScene::handleEvent(Event &event) {
    switch (event.type) {
        case Event::NEW_CHATTING:
            {
                this->_chattingWith = event.data.newChatting.newClient;
                for (auto *message: this->_messages)
                    this->_messagesLayout->removeItem(message->getLayout());
                    this->_messages.clear();
            }
            break;
        case Event::NEW_MESSAGE:
            {
                auto newMessage = event.data.newMessage.message;
                if (newMessage->getAuthor()->getUsername() != this->_chattingWith->getUsername() && newMessage->getAuthor()->getUsername() != this->_clientManager->self->getUsername())
                    return;
                MessageBox *message = new MessageBox(newMessage->getAuthor(), {newMessage});

                this->_messages.push_back(message);
                this->_messagesLayout->addLayout(message->getLayout());
                // TODO group message and append it to the vector
            }
            break;
        case Event::NEW_BULK_MESSAGE:
            {
                auto newMessage = event.data.newBulkMessage.messages;
                // TODO only add messages created by self and chatting user
            }
            break;
        default:
            break;
    }
}

std::shared_ptr<SceneManager> ChatScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

QWidget *ChatScene::getWidget() {
    return (this->_scrollArea);
}

void ChatScene::_initLayouts() {
    this->_messagesLayout = new QVBoxLayout(this->_parent);
}

void ChatScene::_initWidgets() {
    this->_scrollArea = new QScrollArea();
    this->_parent = new QWidget();

    auto groupedMessages = this->_groupMessagesByTime(this->_clientManager->getChatting());

    for (auto messages: groupedMessages) {
        std::shared_ptr<Client> client = messages[0]->getAuthor();
        MessageBox *message = new MessageBox(client, messages);
        this->_messages.push_back(message);
    }
}

void ChatScene::_placeWidgets() {
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_scrollArea->setWidget(this->_parent);
    this->_scrollArea->setWidgetResizable(true);
    // this->_parent->setFixedWidth(700);
    this->_scrollArea->setFixedHeight(555);
    this->_messagesLayout->setSpacing(10);

    for (auto *message: this->_messages)
        this->_messagesLayout->addLayout(message->getLayout());
    this->_messagesLayout->addStretch();
    QTimer::singleShot(0, [this]() {
        QScrollBar *vScrollBar = _scrollArea->verticalScrollBar();
        vScrollBar->setValue(vScrollBar->maximum());
    });
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
    for (const auto &message : allMessages) {
        if (messages.empty() || message->getAuthor() != lastMessage->getAuthor() || message->getTimestamp() - lastMessage->getTimestamp() > 3) {
            // create a new vector if this is the first message or if there's a time gap
            messages.emplace_back();
        }
        lastMessage = message;
        messages.back().push_back(message);
    }

    return (messages);
}