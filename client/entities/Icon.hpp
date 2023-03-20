#pragma once

#include <QWidget>

namespace babel {
    class Icon : public QWidget {
        public:
            Icon(const std::string &input, QWidget *parent = nullptr, int size = 64);

        protected:
            void paintEvent(QPaintEvent *event) override;

        private:
            std::string _seed;
            int _size;
            std::string _generateSeed(const std::string &input);
    };
}
