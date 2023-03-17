#pragma once

#include <QWidget>

namespace babel {

    class Scene;

    class SceneManager {
        public:
            SceneManager(std::shared_ptr<QWidget> widget);
            
            std::shared_ptr<QWidget> getWidget();

            // will clear up the previous scene first.
            void setScene(Scene *scene);

        private:
            std::shared_ptr<QWidget> _widget = nullptr;
            std::unique_ptr<Scene> _scene = nullptr;
    };

}
