#pragma once

#include "SceneManager.hpp"

#include <QWidget>
#include <string>

namespace babel {
    class Scene {
        public:
            virtual ~Scene() {}
    
            virtual std::string getName() = 0;
            virtual void display() = 0;
            virtual void clear() = 0;
            virtual void refresh() = 0;
    };

}
