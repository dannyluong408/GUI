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

    private slots:
        void pageLeft();
        void pageRight();

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
};


#endif // POPUPFRAME_H
