#pragma once

#include "../ClientManager.hpp"
#include "../entities/Contact.hpp"
#include "Scene.hpp"

#include <QHBoxLayout>
#include <QToolButton>

namespace babel {
    class ChatInfoScene : public Scene {
        public:
            ChatInfoScene(std::shared_ptr<ClientManager>);
            ~ChatInfoScene() override;
    
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

            void _callUp();
            void _hangUp();
    
            QLabel *_userLabel = nullptr;
            QToolButton *_callUpButton = nullptr;
            QToolButton *_hangUpButton = nullptr;
            QToolButton *_callUpAbsentButton = nullptr;
            QToolButton *_hangUpAbsentButton = nullptr;
            QHBoxLayout *_userLayout = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
