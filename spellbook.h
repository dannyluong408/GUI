#ifndef SpellBook_H
#define SpellBook_H

#pragma once

#include <QtWidgets>
#include "dragpushbutton.h"



class SpellBook : public QFrame
{
    Q_OBJECT
    public:
        SpellBook(QWidget *parent);
        ~SpellBook();

    public slots:
        void resizeMe(QSize newSize);
        void hideButtons(int tab);

    private slots:
        void pageTurn();

    private:
        QLabel *frameTitle;
        QTabWidget *frameTabWidget;
        QWidget *frameTabs[6];
        QStackedWidget *frameStack[4];
        QGridLayout *frameGrid[4];
        QFrame *spellSlotFrame[60];
        QHBoxLayout *spellSlotFrameLayout[60];
        PushButton *spellSlot[60];
        QLabel *spellSlotDesc[60];
        QVBoxLayout *mainLayout;
        uint32_t spellCount;
        QPushButton *testL,*testR;
};


#endif // SpellBook_H
