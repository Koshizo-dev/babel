#pragma once

#include "../ClientManager.hpp"
#include "Scene.hpp"
#include "../entities/NamedTextField.hpp"

#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>

namespace babel {
    class LoggingScene : public Scene {
        public:
            LoggingScene(std::shared_ptr<ClientManager> clientManager);
            ~LoggingScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;
            void handleEvent(Event &event) override;
            std::shared_ptr<SceneManager> getSceneManager() override;

        private:
            void _loggingButtonClicked();
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();

            QPushButton *_loggingButton = nullptr;
            NamedTextField *_usernameField = nullptr;
            NamedTextField *_serverField = nullptr;
            NamedTextField *_portField = nullptr;
            QLabel *_errorMessage = nullptr;
            QBoxLayout *_topLayout = nullptr;
            QBoxLayout *_layout = nullptr;
            QWidget *_widget = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
            bool _loggingAction = false;
    };

}
