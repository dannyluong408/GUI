#ifndef POPUPFRAME_H
#define POPUPFRAME_H

#include <QtWidgets>




class PopupFrame : public QFrame
{
    Q_OBJECT
    public:
        PopupFrame(QWidget *parent);

    public slots:
        void resizeMe(QSize newSize);
        void toggleMe();


};


#endif // POPUPFRAME_H
