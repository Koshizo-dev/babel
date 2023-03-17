#pragma once

#include "Scene.hpp"

#include <QPushButton>

namespace babel {
    class MainScene : public Scene {
        public:
            MainScene(std::shared_ptr<SceneManager> sceneManager);
            ~MainScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;

        private:
            std::shared_ptr<SceneManager> _sceneManager = nullptr;
    
            std::shared_ptr<QWidget> _parent = nullptr;
            std::unique_ptr<QPushButton> _button = nullptr;
    };

}
