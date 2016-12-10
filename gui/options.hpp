#pragma once

#include <QtWidgets>
#include "GUI/keybindmenu.hpp"

class OptionsFrame : public QFrame
{
    Q_OBJECT
    public:
        OptionsFrame(QWidget *parent);
        void copyShortcut(QShortcut *shortcut[]);

    public slots:
        void currentOption();
        void resizeMe(QSize newSize);
        void updateKeybinds(QString *keybinds);

    signals:
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
