#pragma once


#include <QtWidgets>


class UnitFrame : public QFrame
{
    Q_OBJECT
    public:
        UnitFrame(QWidget *parent);
        void setAvatar(QPixmap newAva);
        void setIsParty(bool party);
        void setScale(double scale);

    public slots:
        void resizeMe(QSize newSize);

    private:
        QLabel *unitIcon, *name;
        QProgressBar *health;
        QProgressBar *mana;
        QPixmap avatar;
        QString unitName;
        bool isParty;
        double partyScale;
};

