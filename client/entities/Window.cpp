#include "Window.hpp"

using namespace babel;

Window::Window(std::shared_ptr<ClientManager> clientManager) {
    this->_clientManager = clientManager;
    this->setGeometry(0, 0, 1280, 720);
}
