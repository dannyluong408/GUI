#ifndef UNITFRAME_H
#define UNITFRAME_H

#pragma once


#include <QtWidgets>


class UnitFrame : public QFrame
{
    Q_OBJECT
    public:
        UnitFrame(QWidget *parent);
        void setAvatar(QPixmap newAva);

    public slots:
        void resizeMe(QSize newSize);

    private:
        QLabel *unitIcon;
        QProgressBar *health;
        QProgressBar *mana;
        QPixmap avatar;
};





#endif // UNITFRAME_H
