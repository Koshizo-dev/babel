#include "ContactScene.hpp"
#include "../ClientError.hpp"
#include <iostream>

using namespace babel;

ContactScene::ContactScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing ContactScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_initLayouts();
    this->_placeWidgets();
    this->clear();
}

ContactScene::~ContactScene() {
    this->_contacts.clear();
    this->_contactsLayout.reset();
    this->_scrollArea.reset();
    this->_parent->setParent(nullptr);
    this->_parent.reset();
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

std::shared_ptr<QWidget> ContactScene::getWidget() {
    return (this->_scrollArea);
}

void ContactScene::_initLayouts() {
    this->_contactsLayout = std::shared_ptr<QVBoxLayout>(new QVBoxLayout(this->_parent.get()));
}

void ContactScene::_initWidgets() {
    this->_scrollArea = std::shared_ptr<QScrollArea>(new QScrollArea());
    this->_parent = std::shared_ptr<QWidget>(new QWidget());

    for (std::shared_ptr<Client> client: this->_clientManager->clients) {
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
    this->_scrollArea->setFixedHeight(555);

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
