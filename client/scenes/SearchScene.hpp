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
            void handleEvent(Event &event) override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            QLayout *getLayout();
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
    
            QLineEdit *_searchInput = nullptr;
            QHBoxLayout *_searchLayout = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
