#ifndef BUFFFRAME_H
#define BUFFFRAME_H

#include <QtWidgets>
#include "bufficon.h"
#include <vector>


class BuffFrame : public QFrame
{
    Q_OBJECT
    public:
        BuffFrame(QWidget *parent);
        void insertBuff(BuffIcon* buff);
//      void removeBuff(BuffIcon* buff);

    public slots:
        void resizeMe(QSize newSize);

    private:
        std::vector<BuffIcon*> buffs;
};



#endif // BUFFFRAME_H
