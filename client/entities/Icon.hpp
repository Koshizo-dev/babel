#pragma once

#include <QWidget>

namespace babel {
    class Icon : public QWidget {
        public:
            Icon(const std::string &input, QWidget *parent = nullptr);

        protected:
            void paintEvent(QPaintEvent *event) override;

        private:
            std::string _seed;
            std::string _generateSeed(const std::string &input);
    };
}
