#include "ContactScene.hpp"
#include "../ClientError.hpp"
#include <iostream>
#include <qnamespace.h>
#include <qsizepolicy.h>

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
    std::string contactFilter = this->getSceneManager()->getContactFilter();
    for (auto *contact: this->_contacts) {
        contact->updateChatting();
        if (contact->getClient()->getUsername().substr(0, contactFilter.size()) != contactFilter)
            contact->getButton()->hide();
        else
            contact->getButton()->show();
    }
    this->_parent->repaint();
    // TODO refresh clients
}

std::shared_ptr<SceneManager> ContactScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

QWidget *ContactScene::getWidget() {
    return (this->_scrollArea);
}

void ContactScene::_initLayouts() {
    this->_contactsLayout = new QVBoxLayout(this->_parent);
}

void ContactScene::_initWidgets() {
    this->_scrollArea = new QScrollArea();
    this->_parent = new QWidget();

    for (auto client: this->_clientManager->clients) {
        auto *contact = this->_generateContact(client);
        this->_contacts.push_back(contact);
    }

    // sort the contacts by message timestamps
    std::sort(this->_contacts.begin(), this->_contacts.end(),
              [](const Contact *a, const Contact *b) { 
            long aTimestamp = 0;
            if (a->getClient()->getMessages().size() != 0)
                aTimestamp = a->getClient()->getMessages()[a->getClient()->getMessages().size()-1]->getTimestamp();
            long bTimestamp = 0;
            if (b->getClient()->getMessages().size() != 0)
                bTimestamp = b->getClient()->getMessages()[b->getClient()->getMessages().size()-1]->getTimestamp();
            return aTimestamp > bTimestamp;
        });
}

void ContactScene::_placeWidgets() {
    this->_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_scrollArea->setWidget(this->_parent);
    this->_scrollArea->setWidgetResizable(true);
    this->_parent->setFixedWidth(364);
    this->_scrollArea->setFixedHeight(555);

    this->_contactsLayout->setMargin(0);
    this->_contactsLayout->setSpacing(5);

    for (auto *contact: this->_contacts) {
        this->_contactsLayout->addWidget(contact->getButton(), 0, Qt::AlignTop);
    }

    this->_contactsLayout->addStretch();

    this->refresh();
}

Contact *ContactScene::_generateContact(std::shared_ptr<Client> client) {
    Contact *contact = new Contact(client);

    QObject::connect(contact->getButton(), &QPushButton::clicked, [=]() {
        if (contact->getClient()->isChatting())
            return;
        // TODO change the ChatScene
        std::cout << "Interacted with client " << contact->getClient()->getUsername() << "!" << std::endl;
        this->_clientManager->getChatting()->setChatting(false);
        contact->getClient()->setChatting(true);
        this->getSceneManager()->setContactFilter("");
        this->getSceneManager()->getScene()->refresh();
    });
    return (contact);
}
