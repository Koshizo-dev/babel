#pragma once

#include "Scene.hpp"

#include <QPushButton>

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
            bool _loggingAction = false;
    };

}
