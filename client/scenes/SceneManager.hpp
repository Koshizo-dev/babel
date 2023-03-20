#pragma once

#include <QWidget>

namespace babel {

    class Scene;

    class SceneManager {
        public:
            SceneManager(std::shared_ptr<QWidget> widget);

            std::shared_ptr<QWidget> getWidget(void);

            // will clear up the previous scene first.
            void setScene(Scene *scene);

            Scene *getScene(void);

            std::string getContactFilter();
            void setContactFilter(std::string contactFilter);

        private:
            std::shared_ptr<QWidget> _widget = nullptr;
            std::shared_ptr<Scene> _scene = nullptr;
            std::string _contactFilter = "";
    };

}
