#pragma once

#include "../ClientManager.hpp"
#include "UserScene.hpp"
#include "ContactScene.hpp"
#include "SearchScene.hpp"
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
            void _initWidgets();
            void _initLayouts();
            void _placeWidgets();
    
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    
            std::shared_ptr<QWidget> _parent = nullptr;
            std::unique_ptr<UserScene> _user = nullptr;
            std::unique_ptr<ContactScene> _contacts = nullptr;
            std::unique_ptr<SearchScene> _search = nullptr;
            std::shared_ptr<QWidget> _leftSide = nullptr;
            std::unique_ptr<QVBoxLayout> _leftSideLayout = nullptr;
    };

}
