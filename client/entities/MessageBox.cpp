#include "MessageBox.hpp"
#include <qsizepolicy.h>

using namespace babel;

MessageBox::MessageBox(std::shared_ptr<Client> client, std::vector<std::shared_ptr<Message>> messages) {
    this->_client = client;
    this->_messages = messages;
    this->_initElements();
    this->_joinElements();
}

MessageBox::~MessageBox() {
}

std::shared_ptr<Client> MessageBox::getClient() {
    return (this->_client);
}

std::shared_ptr<QHBoxLayout> MessageBox::getLayout() {
    return (this->_layout);
}

void MessageBox::_initElements() {
    std::string name = this->_client->getUsername();
    this->_userLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
    this->_messageLayout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout());
    this->_messageLayout->setObjectName("messageLayout");
    this->_userLabel = std::shared_ptr<QLabel>(new QLabel(name.c_str()));
    this->_layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
    this->_layout->setObjectName("Layout");
    this->_userIcon = this->_client->getNewIcon(32);

    for (std::shared_ptr<Message> message: this->_messages)
        this->_messageLabels.push_back(this->_generateMessage(message));
}

void MessageBox::_joinElements() {
    this->_userLayout->addWidget(this->_userIcon.get());
    this->_userLayout->addWidget(this->_userLabel.get(), 0, Qt::AlignTop);
    this->_messageLayout->addLayout(this->_userLayout.get());

    for (std::shared_ptr<QLabel> messageLabel: this->_messageLabels) {
        auto layout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
        layout->addSpacing(this->_userIcon->width() + messageLabel->font().pointSize());
        layout->addWidget(messageLabel.get());
        this->_messageLayout->addLayout(layout.get());
        this->_messageLayouts.push_back(layout);
    }

    this->_messageLayout->setContentsMargins(0, 0, 0, -200);

    this->_layout->addLayout(this->_messageLayout.get());
    this->_layout->setContentsMargins(0, 0, 0, 0);
}

std::shared_ptr<QLabel> MessageBox::_generateMessage(std::shared_ptr<Message> message) {
    std::shared_ptr<QLabel> messageLabel = std::shared_ptr<QLabel>(new QLabel(message->getContent().c_str()));
    messageLabel->setStyleSheet("font-size: 16px;");

    return (messageLabel);
}
