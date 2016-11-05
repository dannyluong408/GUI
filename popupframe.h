#ifndef POPUPFRAME_H
#define POPUPFRAME_H

#pragma once

#include <QtWidgets>
#include "dragpushbutton.h"



class PopupFrame : public QFrame
{
    Q_OBJECT
    public:
        PopupFrame(QWidget *parent);
        ~PopupFrame();

    public slots:
        void resizeMe(QSize newSize);
        void toggleMe();


    private:
        QLabel *frameTitle;
        QTabWidget *frameTabWidget;
        QWidget *frameTabs[4];
        QGridLayout *frameGrid[4];
        QFrame *spellSlotFrame[32];
        QHBoxLayout *spellSlotFrameLayout[32];
        PushButton *spellSlot[32];
        QLabel *spellSlotDesc[32];
        QVBoxLayout *mainLayout;
        uint32_t spellCount;

};


#endif // POPUPFRAME_H
