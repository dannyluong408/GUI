#ifndef PARTYFRAME_HPP
#define PARTYFRAME_HPP


#pragma once

#include <QtWidgets>
#include "unitframe.h"



class PartyFrame : public QFrame
{
    Q_OBJECT
    public:
        PartyFrame(QWidget *parent);
    public slots:
        void resizeMe(QSize newSize);
    private:
        QVBoxLayout *mainLayout;
        UnitFrame *player[2];
        double scale;

};
#endif // PARTYFRAME_HPP
