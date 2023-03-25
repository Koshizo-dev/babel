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
    
            const std::string getName() const override;
            const void display() override;
            const void clear() override;
            const void refresh() override;
            const void handleEvent(Event &event) override;
            const std::shared_ptr<SceneManager> getSceneManager() const override;
            QWidget *getWidget();
            
        private:
            const void _initLayouts();
            const void _initWidgets();
            const void _placeWidgets();
    
            QLabel *_userLabel = nullptr;
            QToolButton *_logoutButton = nullptr;
            QHBoxLayout *_userLayout = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
