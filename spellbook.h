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
        void setSlotSpell(int slot, uint32_t spellId);

    public slots:
        void resizeMe(QSize newSize);
        void hideButtons(int tab);
        void greyButtons(int index);
        void hide();

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
        QPushButton *pageL,*pageR,*x;
};


#endif // SpellBook_H
