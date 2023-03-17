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
    this->_button = std::unique_ptr<QPushButton>(new QPushButton("Hello world !"));

    int x = centerX(this->_sceneManager->getWidget().get(), this->_button->width());
    int y = centerY(this->_sceneManager->getWidget().get(), this->_button->height());
    this->_button->move(x, y);
    
    QObject::connect(this->_button.get(), &QPushButton::clicked, [=]() {
        this->_sceneManager->setScene(new LoggingScene(this->_sceneManager));
    });
    printf("main scene created!\n");
}

MainScene::~MainScene() {
    this->_button.reset();
}

std::string MainScene::getName() {
    return "Main menu";
}

void MainScene::display() {
    this->_button->setParent(this->_sceneManager->getWidget().get());
    this->_sceneManager->getWidget()->update();
    this->_sceneManager->getWidget()->repaint();
}

void MainScene::clear() {
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void MainScene::refresh() {
}
