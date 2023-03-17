#pragma once

#include "Scene.hpp"
#include "../entities/NamedTextField.hpp"
#include "SceneManager.hpp"

#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>

namespace babel {
    class LoggingScene : public Scene {
        public:
            LoggingScene(std::shared_ptr<SceneManager> sceneManager);
            ~LoggingScene() override;
    
            std::string getName() override;
            void display() override;
            void clear() override;
            void refresh() override;

        private:
            void _loggingButtonClicked();
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();

            std::shared_ptr<SceneManager> _sceneManager;

            std::shared_ptr<QWidget> _widget = nullptr;
            std::unique_ptr<QPushButton> _loggingButton = nullptr;
            std::unique_ptr<NamedTextField> _usernameField = nullptr;
            std::unique_ptr<NamedTextField> _serverField = nullptr;
            std::unique_ptr<NamedTextField> _portField = nullptr;
            std::unique_ptr<QBoxLayout> _topLayout = nullptr;
            std::unique_ptr<QBoxLayout> _layout = nullptr;
            std::unique_ptr<QLabel> _errorMessage = nullptr;
            bool _loggingAction = false;
    };

}
