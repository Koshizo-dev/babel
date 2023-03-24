#include "MessageBox.hpp"
#include <iostream>

using namespace babel;

MessageBox::MessageBox(std::shared_ptr<Client> client, std::vector<std::shared_ptr<Message>> messages) {
    this->_client = client;
    this->_messages = messages;
    this->_initElements();
    this->_joinElements();
}

std::shared_ptr<Client> MessageBox::getClient() {
    return (this->_client);
}

QLayout *MessageBox::getLayout() {
    return (this->_layout);
}

void MessageBox::_initElements() {
    std::string name = this->_client->getUsername();
    this->_userLayout = new QHBoxLayout();
    this->_messageLayout = new QVBoxLayout();
    this->_userLabel = new QLabel(name.c_str());
    this->_layout = new QHBoxLayout();
    this->_userIcon = this->_client->getIcon(32);

    for (std::shared_ptr<Message> message: this->_messages)
        this->_messageLabels.push_back(this->_generateMessage(message));
}

void MessageBox::_joinElements() {
    this->_userLayout->addWidget(this->_userIcon);
    this->_userLayout->addWidget(this->_userLabel, 0, Qt::AlignTop);
    this->_messageLayout->addLayout(this->_userLayout);

    for (QLabel *messageLabel: this->_messageLabels) {
        auto layout = new QHBoxLayout();
        layout->addSpacing(this->_userIcon->width() + messageLabel->font().pointSize());
        layout->addWidget(messageLabel);
        this->_messageLayout->addLayout(layout);
        this->_messageLayouts.push_back(layout);
    }

    this->_layout->addLayout(this->_messageLayout);
    this->_layout->setContentsMargins(0, 0, 0, 0);
}

QLabel *MessageBox::_generateMessage(std::shared_ptr<Message> message) {
    auto messageLabel = new QLabel(message->getContent().c_str());
    messageLabel->setStyleSheet("font-size: 16px;");

    return (messageLabel);
}
