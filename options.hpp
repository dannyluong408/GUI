#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#pragma once

#include <QtWidgets>
#include "keybindmenu.hpp"

class OptionsFrame : public QFrame
{
    Q_OBJECT
    public:
        OptionsFrame(QWidget *parent);

    public slots:
        void currentOption();
        void updateKeybinds(QString *keybinds);
        void resizeMe(QSize newSize);

    signals:
        void disableShortcuts();
        void enableShortcuts();
        void newBindSend(QKeySequence newBind, int num);
        void saveBinds();
        void defaultBinds();
        void resizeChildren(QSize newSize);

    private:
        QHBoxLayout *mainLayout;
        QVBoxLayout *buttonLayout;
        QVBoxLayout *optionLayout, *optionFrameLayout[6];
        QPushButton *options[6];
        QStackedWidget *optionsStacked;
        QFrame *optionFrame[6], *buttonFrame, *mainFrame;
        KeybindMenu *keybindMenu;
};

#endif // OPTIONS_HPP
