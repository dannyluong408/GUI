#pragma once

#include <QtWidgets>

class HonorFrame : public QFrame
{
    Q_OBJECT
    public:
        HonorFrame(QWidget *parent);
    public slots:
        void resizeMe(QSize size);
        void hide();

    private:
        QLabel *honorName,*honorLogo;
        QPushButton *x;
        QPixmap honorLogoPix;

};

