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
    
            const std::string getName() const override;
            const void display() override;
            const void clear() override;
            const void refresh() override;
            const void handleEvent(Event &event) override;
            const std::shared_ptr<SceneManager> getSceneManager() const override;

        private:
            const void _loggingButtonClicked();
            const void _initLayouts();
            const void _initWidgets();
            const void _placeWidgets();

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
