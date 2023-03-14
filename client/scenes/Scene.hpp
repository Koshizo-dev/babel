#pragma once

#include <QWidget>
#include <string>

namespace babel {
    class Scene {
        public:
            virtual std::string getName() = 0;
            virtual void load(std::shared_ptr<QWidget> parent) = 0;
            virtual void display() = 0;
            virtual void clear() = 0;
            virtual void refresh() = 0;
    };

}
