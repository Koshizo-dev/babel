#pragma once

#include "SceneManager.hpp"
#include "../Event.hpp"

#include <QWidget>
#include <string>

namespace babel {
    class Scene {
        public:
            virtual ~Scene() {}

            virtual const std::string getName() const = 0;
            virtual const void display() = 0;
            virtual const void clear() = 0;
            virtual const void refresh() = 0;
            virtual const void handleEvent(Event &event) = 0;
            virtual const std::shared_ptr<SceneManager> getSceneManager() const = 0;
    };

}
