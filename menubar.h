#ifndef MENUBAR_H
#define MENUBAR_H

#include <QtWidgets>
#include <dragpushbutton.h>

class Menubar: public QFrame
{
    Q_OBJECT
    public:
        Menubar(QWidget *parent);
    public slots:
        void resizeMe(QSize newSize);

    private:
        PushButton *menuButton[5];

};

#endif // MENUBAR_H
