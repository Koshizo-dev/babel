#pragma once

#include "../ClientManager.hpp"
#include "../entities/MessageBox.hpp"
#include "Scene.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

namespace babel {
    class ChatScene : public Scene {
        public:
            ChatScene(std::shared_ptr<ClientManager>);
            ~ChatScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            void handleEvent(Event &event) override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            QWidget *getWidget();

        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
            std::vector<std::vector<std::shared_ptr<Message>>> _groupMessagesByTime(std::shared_ptr<Client> client1);

            std::vector<MessageBox*> _messages = {};
            QVBoxLayout* _messagesLayout = nullptr;
            QScrollArea* _scrollArea = nullptr;
            QWidget* _parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
            std::shared_ptr<Client> _chattingWith = nullptr;
    };
}
