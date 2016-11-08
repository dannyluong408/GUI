#ifndef BUFFFRAME_H
#define BUFFFRAME_H

#include <QtWidgets>
#include "bufficon.h"


class BuffFrame : public QFrame
{
    Q_OBJECT
    public:
        BuffFrame(QWidget *parent);
//      void insertBuff(BuffIcon* buff);
//      void removeBuff(BuffIcon* buff);
        void test();

        void sort();


    public slots:
        void resizeMe(QSize newSize);

    private:
        QGridLayout *buffLayout;
        QVector<BuffIcon*> buffs;
};



#endif // BUFFFRAME_H
