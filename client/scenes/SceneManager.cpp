#include "SceneManager.hpp"
#include "Scene.hpp"

using namespace babel;

SceneManager::SceneManager(QWidget *widget) {
    this->_widget = widget;
}

QWidget *SceneManager::getWidget(void) {
    return (this->_widget);
}

void SceneManager::setScene(Scene *scene) {
    this->_scene.reset();
    this->_scene = std::shared_ptr<Scene>(scene);
    this->_scene->display();
}

std::shared_ptr<Scene> SceneManager::getScene(void) {
    return (this->_scene);
}

std::string SceneManager::getContactFilter() {
    return (this->_contactFilter);
}

void SceneManager::setContactFilter(std::string contactFilter) {
    this->_contactFilter = contactFilter;
}
