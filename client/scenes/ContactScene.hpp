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
    
            const std::string getName() const override;
            const void display() override;
            const void clear() override;
            const void refresh() override;
            const void handleEvent(Event &event) override;
            const std::shared_ptr<SceneManager> getSceneManager() const override;
            QWidget *getWidget();
            
        private:
            const void _initLayouts();
            const void _initWidgets();
            const void _placeWidgets();
            Contact *_generateContact(std::shared_ptr<Client> client);
    
            std::vector<Contact*> _contacts = {};
            QVBoxLayout *_contactsLayout = nullptr;
            QScrollArea *_scrollArea = nullptr;
            QWidget *_parent = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    };
}
