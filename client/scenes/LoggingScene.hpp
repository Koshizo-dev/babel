#pragma once

#include "Scene.hpp"
#include "../entities/NamedTextField.hpp"

#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>

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
            void _initLayouts();
            void _initWidgets();
            void _placeWidgets();

            std::shared_ptr<QWidget> _parent = nullptr;
            std::shared_ptr<QWidget> _widget = nullptr;
            std::unique_ptr<QPushButton> _loggingButton = nullptr;
            std::unique_ptr<NamedTextField> _usernameField = nullptr;
            std::unique_ptr<NamedTextField> _serverField = nullptr;
            std::unique_ptr<NamedTextField> _portField = nullptr;
            std::unique_ptr<QBoxLayout> _topLayout = nullptr;
            std::unique_ptr<QBoxLayout> _layout = nullptr;
            bool _loggingAction = false;
    };

}
