#pragma once
#include <QtWidgets>
#include "bufficon.h"


class TargetBuffFrame : public QFrame
{
    Q_OBJECT
    public:
        TargetBuffFrame(QWidget *parent);
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
        void shiftMe(bool shicccft);

    private:
        QGridLayout *buffLayout;
        QVector<BuffIcon*> buffs;
        bool isDebuff;
};
