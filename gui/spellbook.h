#pragma once
#include "GUI/dragicon.hpp"
#include <QtWidgets>


class SpellBook : public QFrame
{
    Q_OBJECT
    public:
        SpellBook(QWidget *parent);
        void setSlotSpell(int slot, uint32_t spellId);
        uint32_t getCursorID();

    public slots:
        void resizeMe(QSize newSize);
        void hideButtons(int tab);
        void greyButtons(int index);
        void hide();

    private slots:
        void pageTurn();

    signals:
        void spellPickedUp(const uint32_t spellid);

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
