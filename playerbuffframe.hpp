#pragma once

#include <QtWidgets>
#include "bufficon.h"


class PlayerBuffFrame : public QFrame
{
    Q_OBJECT
    public:
        PlayerBuffFrame(QWidget *parent);
//      void insertBuff(BuffIcon* buff);
//      void removeBuff(BuffIcon* buff);
        void test();
        void sort();
        void setAsDebuff(bool state);

    signals:
        //use this to shift debuffs down if buffs > 10
        void bumpDown(bool shift);

    public slots:
        void resizeMe(QSize newSize);
        void shiftMe(bool shift);

    private:
        QGridLayout *buffLayout;
        QVector<BuffIcon*> buffs;
        bool isDebuff;
};
