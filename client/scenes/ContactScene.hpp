#pragma once

#include "../ClientManager.hpp"
#include "../entities/Contact.hpp"
#include "Scene.hpp"

#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

namespace babel {
    class ContactScene : public Scene {
        public:
            ContactScene(std::shared_ptr<ClientManager>);
            ~ContactScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            void handleEvent(Event &event) override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            QWidget *getWidget();
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
            Contact *_generateContact(std::shared_ptr<Client> client);
    
            std::vector<Contact*> _contacts = {};
            QVBoxLayout *_contactsLayout = nullptr;
            QScrollArea *_scrollArea = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };
}
