#ifndef BUFFICON_H
#define BUFFICON_H



#include <QtWidgets>


class BuffIcon : public QLabel
{
    Q_OBJECT
    public:
        BuffIcon(QWidget *parent);
        //QPixmap getOGPix();
        void setOGPix(const QPixmap *ogPix);

    public slots:
        void resizeMe(QSize newSize);

    private:
        QPixmap origPix;
};



#endif // BUFFICON_H
