#pragma once

#include <QtWidgets>
#include "GUI/bufficon.h"


class PlayerBuffFrame : public QFrame
{
    Q_OBJECT
    public:
        PlayerBuffFrame(QWidget *parent);
        void insertBuff(uint32_t buffid);
        void removeBuff(uint32_t buffid);
        void test(bool buff);
        void sort(bool buff);

    signals:
        //use this to shift debuffs down if buffs > 10
        void bumpDown(bool shift);

    public slots:
        void resizeMe(QSize newSize);
        void shiftMe(bool shift);

    private:
        QFrame *buffFrame, *debuffFrame;
        QGridLayout *buffLayout, *debuffLayout;
        QVector<BuffIcon*> buffs, debuffs;
};
