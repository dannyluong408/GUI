#ifndef BUFFICON_H
#define BUFFICON_H

#pragma once

#include <QtWidgets>


class BuffIcon : public QLabel
{
    Q_OBJECT
    public:
        BuffIcon(QWidget *parent);
        //QPixmap getOGPix();
        void setOGPix(const QPixmap *ogPix);
        void setBuffDuration(uint64_t time);
        uint64_t getBuffDuration() const;

    public slots:
        void resizeMe(QSize newSize);

    private:
        uint32_t buffID;
        uint32_t buff_type;
        QPixmap origPix;
        uint64_t end_time;
};



#endif // BUFFICON_H
