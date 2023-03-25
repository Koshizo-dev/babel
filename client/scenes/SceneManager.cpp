#include "SceneManager.hpp"
#include "Scene.hpp"

using namespace babel;

SceneManager::SceneManager(QWidget *widget) {
    this->_widget = widget;
}

QWidget *SceneManager::getWidget(void) {
    return (this->_widget);
}

const void SceneManager::setScene(Scene *scene) {
    this->_scene.reset();
    this->_scene = std::shared_ptr<Scene>(scene);
    this->_scene->display();
}

const std::shared_ptr<Scene> SceneManager::getScene(void) const {
    return (this->_scene);
}
