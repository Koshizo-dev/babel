#include "MainScene.hpp"
#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"
#include <QObject>
#include <iostream>

using namespace babel;

MainScene::MainScene(std::shared_ptr<ClientManager> clientManager) {
    if (clientManager == nullptr)
        throw ClientError("Whilst initializing LoggingScene: ClientManager cannot be null !");
    this->_clientManager = clientManager;
    this->_initWidgets();
    this->_placeWidgets();
    this->clear();
}

MainScene::~MainScene() {
    this->_button.reset();
    this->_contacts.reset();
}

std::string MainScene::getName() {
    return "Main menu";
}

void MainScene::display() {
    this->_contacts->display();
    this->_parent->show();
}

void MainScene::clear() {
    this->_contacts->clear();
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void MainScene::refresh() {
    this->_contacts->refresh();
    this->_parent->repaint();
}

std::shared_ptr<SceneManager> MainScene::getSceneManager() {
    return (this->_clientManager->sceneManager);
}

void MainScene::_initWidgets() {
    this->_parent = std::shared_ptr<QWidget>(new QWidget(this->getSceneManager()->getWidget().get()));
    this->_button = std::unique_ptr<QPushButton>(new QPushButton("Hello world !", this->_parent.get()));
    this->_contacts = std::unique_ptr<ContactScene>(new ContactScene(this->_clientManager, this->getSceneManager()->getWidget()));
}

void MainScene::_placeWidgets() {
    std::shared_ptr<Icon> icon = this->_clientManager->self->getIcon();
    icon->setParent(this->_parent.get());

    int x = centerX(this->getSceneManager()->getWidget().get(), this->_parent->width());
    int y = centerY(this->getSceneManager()->getWidget().get(), this->_parent->height());
    this->_parent->move(x, y);

    QObject::connect(this->_button.get(), &QPushButton::clicked, [=]() {
        this->getSceneManager()->setScene(new LoggingScene(this->_clientManager));
    });
}
