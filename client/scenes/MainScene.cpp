#include "MainScene.hpp"
#include "LoggingScene.hpp"
#include "../ClientError.hpp"
#include "../utils.hpp"
#include <QObject>
#include <iostream>

using namespace babel;

MainScene::MainScene(std::shared_ptr<SceneManager> sceneManager) {
    if (sceneManager == nullptr)
        throw ClientError("Whilst initializing LoggingScene: SceneManager cannot be null !");
    this->_sceneManager = sceneManager;
    this->_initWidgets();
    this->_placeWidgets();
    this->clear();
}

MainScene::~MainScene() {
    this->_button.reset();
}

std::string MainScene::getName() {
    return "Main menu";
}

void MainScene::display() {
    this->_parent->show();
}

void MainScene::clear() {
    this->_parent->hide();
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void MainScene::refresh() {
    this->_parent->repaint();
}

void MainScene::_initWidgets() {
    this->_parent = std::shared_ptr<QWidget>(new QWidget(this->_sceneManager->getWidget().get()));
    this->_button = std::unique_ptr<QPushButton>(new QPushButton("Hello world !", this->_parent.get()));
}

void MainScene::_placeWidgets() {
    int x = centerX(this->_sceneManager->getWidget().get(), this->_button->width());
    int y = centerY(this->_sceneManager->getWidget().get(), this->_button->height());
    this->_button->move(x, y);
    
    QObject::connect(this->_button.get(), &QPushButton::clicked, [=]() {
        this->_sceneManager->setScene(new LoggingScene(this->_sceneManager));
    });
}
