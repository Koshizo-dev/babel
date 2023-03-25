#pragma once

#include <QWidget>

namespace babel {

    class Scene;

    class SceneManager {
        public:
            SceneManager(QWidget *widget);

            QWidget *getWidget(void);

            // will clear up the previous scene first.
            void setScene(Scene *scene);

            std::shared_ptr<Scene> getScene(void);

        private:
            QWidget *_widget = nullptr;
            std::shared_ptr<Scene> _scene = nullptr;
    };

}
