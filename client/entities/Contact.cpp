#include "Contact.hpp"

using namespace babel;

Contact::Contact(std::shared_ptr<Client> client) {
    this->_client = client;
    this->_initElements();
    this->_joinElements();
}

Contact::~Contact() {
}

std::shared_ptr<Client> Contact::getClient() {
    return (this->_client);
}

std::shared_ptr<QPushButton> Contact::getButton() {
    return (this->_button);
}

std::shared_ptr<QLabel> Contact::getButtonLabel() {
    return (this->_buttonLabel);
}

std::shared_ptr<QHBoxLayout> Contact::getButtonLayout() {
    return (this->_buttonLayout);
}

void Contact::_initElements() {
    std::string name = this->_client->getUsername();
    this->_button = std::shared_ptr<QPushButton>(new QPushButton());
    this->_buttonLayout = std::shared_ptr<QHBoxLayout>(new QHBoxLayout());
    this->_buttonLabel = std::shared_ptr<QLabel>(new QLabel(name.c_str()));
    if (this->_client->isChatting()) {
        this->_button->setStyleSheet("background-color: lightgray");
        this->_buttonLabel->setStyleSheet("background-color: lightgray");
    }
}

void Contact::_joinElements() {
    this->_buttonLayout->addWidget(this->_client->getIcon().get());
    this->_buttonLayout->addWidget(this->_buttonLabel.get());

    this->_button->setLayout(this->_buttonLayout.get());
    this->_buttonLayout->setContentsMargins(0, 0, 0, 0);
    
    // adjust the size of the button to fit both the icon and the label
    int iconWidth = this->_client->getIcon()->width();
    this->_button->setFixedWidth(iconWidth + 300);
    this->_button->setFixedHeight(this->_client->getIcon()->height());
}
