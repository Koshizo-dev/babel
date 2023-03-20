#pragma once

#include "../ClientManager.hpp"
#include "../entities/Contact.hpp"
#include "../entities/ChatBox.hpp"
#include "Scene.hpp"

#include <QTextEdit>
#include <QLayout>

namespace babel {
    class ChatBoxScene : public Scene {
        public:
            ChatBoxScene(std::shared_ptr<ClientManager>);
            ~ChatBoxScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            std::shared_ptr<QLayout> getLayout();
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
    
            std::unique_ptr<ChatBox> _chatBoxInput = nullptr;

            // Isn't really useful here, but left here in case of widgets to the chatbox
            std::shared_ptr<QHBoxLayout> _chatBoxLayout = nullptr;

            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
