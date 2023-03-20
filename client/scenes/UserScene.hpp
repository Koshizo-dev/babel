#pragma once

#include "../ClientManager.hpp"
#include "../entities/Contact.hpp"
#include "Scene.hpp"

#include <QHBoxLayout>
#include <QToolButton>

namespace babel {
    class UserScene : public Scene {
        public:
            UserScene(std::shared_ptr<ClientManager>);
            ~UserScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            std::shared_ptr<QWidget> getWidget();
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
    
            std::unique_ptr<QLabel> _userLabel = nullptr;
            std::unique_ptr<QToolButton> _logoutButton = nullptr;
            std::unique_ptr<QHBoxLayout> _userLayout = nullptr;
            std::shared_ptr<QWidget> _parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
