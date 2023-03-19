#include "ContactScene.hpp"
#include "../ClientError.hpp"
#include <iostream>
#include <qnamespace.h>

using namespace babel;

ContactScene::ContactScene(std::shared_ptr<ClientManager> clientManager, std::shared_ptr<QWidget> mainParent) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_mainParent = mainParent;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ContactScene::~ContactScene() {
}

std::string ContactScene::getName() {
    return "Contact menu";
}

void ContactScene::display() {
    this->_parent->show();
    this->_scrollArea->show();
}

void ContactScene::clear() {
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void ContactScene::refresh() {
    this->_parent->repaint();
    // TODO refresh clients
}

std::shared_ptr<SceneManager> ContactScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

void ContactScene::_initLayouts() {
    this->_contactsLayout = std::unique_ptr<QVBoxLayout>(new QVBoxLayout(this->_parent.get()));
}

void ContactScene::_initWidgets() {
    this->_scrollArea = std::shared_ptr<QScrollArea>(new QScrollArea(this->_mainParent.get()));
    this->_parent = std::shared_ptr<QWidget>(new QWidget(this->_scrollArea.get()));

    for (std::shared_ptr<Client> client: this->_clientManager->clients) {
        std::cout << "initializing client [" << client->getUsername() << "] !" << std::endl;
        std::shared_ptr<Contact> contact = this->_generateContact(client);
        this->_contacts.push_back(contact);
    }
}

void ContactScene::_placeWidgets() {
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_scrollArea->setWidget(this->_parent.get());
    this->_scrollArea->setWidgetResizable(true);
    this->_parent->setFixedWidth(364);

    for (std::shared_ptr<Contact> contact: this->_contacts) {
        this->_contactsLayout->addWidget(contact->getButton().get());
    }
}

std::shared_ptr<Contact> ContactScene::_generateContact(std::shared_ptr<Client> client) {
    std::shared_ptr<Contact> contact = std::shared_ptr<Contact>(new Contact(client));

    QObject::connect(contact->getButton().get(), &QPushButton::clicked, [=]() {
        // TODO change the ChatScene
        std::cout << "Interacted with client " << contact->getClient()->getUsername() << "!" << std::endl;
    });

    return (contact);
}
