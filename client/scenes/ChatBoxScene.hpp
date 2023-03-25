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
    
            const std::string getName() const override;
            const void display() override;
            const void clear() override;
            const void refresh() override;
            const void handleEvent(Event &event) override;
            const std::shared_ptr<SceneManager> getSceneManager() const override;

            QLayout *getLayout();
    
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
    
            ChatBox *_chatBoxInput = nullptr;

            // Isn't really useful here, but left here in case of widgets to the chatbox
            QHBoxLayout *_chatBoxLayout = nullptr;

            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
