#include "MainScene.hpp"
#include "../ClientError.hpp"

using namespace babel;

MainScene::~MainScene() {
    this->_button.reset();
}

std::string MainScene::getName() {
    return "Main menu";
}

// Load the Scene with the parent passed as parameter
// If function already loaded
//     Will call the Scene::clear.
//     Will override the current parent.
void MainScene::load(std::shared_ptr<QWidget> parent) {
    if (this->_parent)
        this->clear();
    this->_parent = parent;
}

void MainScene::display() {
    if (this->_parent == nullptr)
        throw ClientError("MainScene needs to be loaded first!");

    QPushButton button("Hello world !", this->_parent.get());
    button.setGeometry(0, 0, 200, 200);

    //int x = this->centerX(button.width());
    //int y = this->centerX(button.height());
    //button.move(x, y);
}

void MainScene::clear() {
    if (this->_parent == nullptr)
        throw ClientError("MainScene needs to be loaded first!");
}

// Refresh the MainScene
// Mainly used when window size changed by example
// Or any variable that might have been shown on screen was updated.
void MainScene::refresh() {
    if (this->_parent == nullptr)
        throw ClientError("MainScene needs to be loaded first!");
}
