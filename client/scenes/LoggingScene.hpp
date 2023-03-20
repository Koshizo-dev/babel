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
            std::shared_ptr<SceneManager> getSceneManager() override;

        private:
            void _loggingButtonClicked();
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();

            std::unique_ptr<QPushButton> _loggingButton = nullptr;
            std::unique_ptr<NamedTextField> _usernameField = nullptr;
            std::unique_ptr<NamedTextField> _serverField = nullptr;
            std::unique_ptr<NamedTextField> _portField = nullptr;
            std::unique_ptr<QLabel> _errorMessage = nullptr;
            std::unique_ptr<QBoxLayout> _topLayout = nullptr;
            std::unique_ptr<QBoxLayout> _layout = nullptr;
            std::shared_ptr<QWidget> _widget = nullptr;
            std::shared_ptr<ClientManager> _clientManager = nullptr;
            bool _loggingAction = false;
    };

}
