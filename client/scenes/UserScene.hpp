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
            QWidget *getWidget();
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
    
            QLabel *_userLabel = nullptr;
            QToolButton *_logoutButton = nullptr;
            QHBoxLayout *_userLayout = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
