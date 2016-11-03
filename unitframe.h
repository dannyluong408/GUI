#ifndef UNITFRAME_H
#define UNITFRAME_H




#include <QtWidgets>


class UnitFrame : public QFrame
{
    Q_OBJECT
    public:
        UnitFrame(QWidget *parent);

    public slots:
        void resizeMe(QSize newSize);

    private:

};





#endif // UNITFRAME_H
