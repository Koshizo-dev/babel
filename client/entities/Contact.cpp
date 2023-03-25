#include "Contact.hpp"

using namespace babel;

Contact::Contact(std::shared_ptr<Client> client) {
    this->_client = client;
    this->_initElements();
    this->_joinElements();
}

Contact::~Contact() {
}

const std::shared_ptr<Client> Contact::getClient() const {
    return (this->_client);
}

QPushButton *Contact::getButton() const {
    return (this->_button);
}

QLabel *Contact::getButtonLabel() const {
    return (this->_buttonLabel);
}

QHBoxLayout *Contact::getButtonLayout() const {
    return (this->_buttonLayout);
}

const void Contact::updateChatting() const {
    if (this->_client->isChatting()) {
        this->_button->setStyleSheet("background-color: lightgray");
        this->_buttonLabel->setStyleSheet("background-color: lightgray");
    } else {
        this->_button->setStyleSheet("");
        this->_buttonLabel->setStyleSheet("");
    }
}

const void Contact::_initElements() {
    std::string name = this->_client->getUsername();
    this->_button = new QPushButton();
    this->_buttonLayout = new QHBoxLayout();
    this->_buttonLabel = new QLabel(name.c_str());
}

const void Contact::_joinElements() {
    this->_buttonLayout->addWidget(this->_client->getIcon());
    this->_buttonLayout->addWidget(this->_buttonLabel);

    this->_button->setLayout(this->_buttonLayout);
    this->_buttonLayout->setContentsMargins(0, 0, 0, 0);
    
    // adjust the size of the button to fit both the icon and the label
    int iconWidth = this->_client->getIcon()->width();
    this->_button->setFixedWidth(iconWidth + 300);
    this->_button->setFixedHeight(this->_client->getIcon()->height());
}
