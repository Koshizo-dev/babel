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

            const void _updateCallLayout();

            const void _callUp();
            const void _hangUp();

            std::shared_ptr<Client> _chattingWith = nullptr;
    
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
