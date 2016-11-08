#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#pragma once

#include <QtWidgets>

class OptionsFrame : public QFrame
{
    Q_OBJECT
    public:
        OptionsFrame(QWidget *parent);
    public slots:
        void currentOption();

    private:
        QHBoxLayout *mainLayout;
        QVBoxLayout *buttonLayout;
        QPushButton *options[6];
        QStackedWidget *optionsStacked;
        QFrame *optionFrame[6], *buttonFrame;
};

#endif // OPTIONS_HPP
