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
        void disableShortcutsRec();
        void enableShortcutsRec();

    signals:
        void disableShortcutsSend();
        void enableShortcutsSend();

    private:
        QHBoxLayout *mainLayout;
        QVBoxLayout *buttonLayout;
        QPushButton *options[6];
        QStackedWidget *optionsStacked;
        QFrame *optionFrame[6], *buttonFrame;
        KeybindMenu *keybindMenu;
};

#endif // OPTIONS_HPP
