#pragma once

#include "../ClientManager.hpp"
#include "../entities/Contact.hpp"
#include "Scene.hpp"

#include <QLineEdit>
#include <QLayout>

namespace babel {
    class SearchScene : public Scene {
        public:
            SearchScene(std::shared_ptr<ClientManager>);
            ~SearchScene() override;
    
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
    
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    
            std::shared_ptr<QHBoxLayout> _searchLayout = nullptr;
            std::unique_ptr<QLineEdit> _searchInput = nullptr;
    };

}
