#pragma once

#include "Scene.hpp"

namespace babel {
    class MainScene : public Scene {
        public:
            std::string getName() override;
            void load(std::shared_ptr<QWidget> parent) override;
            void display() override;
            void clear() override;
            void refresh() override;

        private:
            std::shared_ptr<QWidget> _parent = nullptr;
    };

}
