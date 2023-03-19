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
            ContactScene(std::shared_ptr<ClientManager>, std::shared_ptr<QWidget> mainParent);
            ~ContactScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            std::shared_ptr<SceneManager> getSceneManager() override;
            
        private:
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();
            std::shared_ptr<Contact> _generateContact(std::shared_ptr<Client> client);
    
            std::shared_ptr<ClientManager> _clientManager = nullptr;
    
            std::shared_ptr<QWidget> _mainParent = nullptr;
            std::shared_ptr<QWidget> _parent = nullptr;
            std::unique_ptr<QVBoxLayout> _contactsLayout = nullptr;
            std::vector<std::shared_ptr<Contact>> _contacts = {};
            std::shared_ptr<QScrollArea> _scrollArea = nullptr;
    };

}
