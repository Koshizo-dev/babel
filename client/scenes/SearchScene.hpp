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
    
            const std::string getName() const override;
            const void display() override;
            const void clear() override;
            const void refresh() override;
            const void handleEvent(Event &event) override;
            const std::shared_ptr<SceneManager> getSceneManager() const override;
            QLayout *getLayout();
            
        private:
            const void _initLayouts();
            const void _initWidgets();
            const void _placeWidgets();
    
            QLineEdit *_searchInput = nullptr;
            QHBoxLayout *_searchLayout = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };

}
