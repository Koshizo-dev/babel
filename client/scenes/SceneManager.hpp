#pragma once

#include <QWidget>

namespace babel {

    class Scene;

    class SceneManager {
        public:
            SceneManager(QWidget *widget);

            QWidget *getWidget(void);

            // will clear up the previous scene first.
            const void setScene(Scene *scene);

            const std::shared_ptr<Scene> getScene(void) const;

        private:
            QWidget *_widget = nullptr;
            std::shared_ptr<Scene> _scene = nullptr;
    };

}
