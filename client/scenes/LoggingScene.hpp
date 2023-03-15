#pragma once

#include "Scene.hpp"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>

namespace babel {
    class LoggingScene : public Scene {
        public:
            ~LoggingScene() override;
    
            std::string getName() override;
            void load(std::shared_ptr<QWidget> parent) override;
            void display() override;
            void clear() override;
            void refresh() override;

        private:
            void _loggingButtonClicked();
    
            std::shared_ptr<QWidget> _parent = nullptr;
            std::unique_ptr<QPushButton> _loggingButton = nullptr;
            std::unique_ptr<QLineEdit> _usernameInput = nullptr;
            std::unique_ptr<QLabel> _usernameLabel = nullptr;
            std::unique_ptr<QHBoxLayout> _usernameLayout = nullptr;
            bool _loggingAction = false;
    };

}
