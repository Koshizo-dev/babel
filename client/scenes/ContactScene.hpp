#pragma once

#include "../ClientManager.hpp"
#include "Scene.hpp"

#include <QPushButton>

namespace babel {
    class ContactScene : public Scene {
        public:
            ContactScene(std::shared_ptr<ClientManager>);
            ~ContactScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;

        private:
            void _initWidgets();
            void _placeWidgets();
    
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    
            std::shared_ptr<QWidget> _parent = nullptr;
            std::unique_ptr<QPushButton> _button = nullptr;
    };

}
