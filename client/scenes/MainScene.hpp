#pragma once

#include "../ClientManager.hpp"
#include "UserScene.hpp"
#include "ContactScene.hpp"
#include "SearchScene.hpp"
#include "ChatBoxScene.hpp"
#include "ChatInfoScene.hpp"
#include "ChatScene.hpp"
#include "Scene.hpp"

#include <QPushButton>

namespace babel {
    class MainScene : public Scene {
        public:
            MainScene(std::shared_ptr<ClientManager> clientManager);
            ~MainScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            std::shared_ptr<SceneManager> getSceneManager() override;

        private:
            void _initLayouts();
            void _initLeftLayout();
            void _initRightLayout();

            void _placeLayouts();
            void _placeLeftLayout();
            void _placeRightLayout();

            std::unique_ptr<UserScene> _user = nullptr;
            std::unique_ptr<ContactScene> _contacts = nullptr;
            std::unique_ptr<SearchScene> _search = nullptr;
            QVBoxLayout *_leftSideLayout = nullptr;

            std::unique_ptr<ChatInfoScene> _chatInfo = nullptr;
            std::unique_ptr<ChatScene> _messages = nullptr;
            std::unique_ptr<ChatBoxScene> _chatBox = nullptr;
            QVBoxLayout *_rightSideLayout = nullptr;

            QHBoxLayout *_parentLayout = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
