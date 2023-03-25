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
            std::vector<std::vector<std::shared_ptr<Message>>> _groupMessagesByTime(std::shared_ptr<Client> client1);

            std::vector<MessageBox*> _messages = {};
            QVBoxLayout* _messagesLayout = nullptr;
            QScrollArea* _scrollArea = nullptr;
            QWidget* _parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
            std::shared_ptr<Client> _chattingWith = nullptr;
    };
}
