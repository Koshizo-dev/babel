#include "SceneManager.hpp"
#include "Scene.hpp"

using namespace babel;

SceneManager::SceneManager(std::shared_ptr<QWidget> widget) {
    this->_widget = widget;
}

std::shared_ptr<QWidget> SceneManager::getWidget(void) {
    return (this->_widget);
}

void SceneManager::setScene(Scene *scene) {
    if (this->_scene) {
        this->_scene.reset();
    }
    this->_scene = std::unique_ptr<Scene>(scene);
    this->_scene->display();
}

Scene *SceneManager::getScene(void) {
    return (this->_scene.get());
}