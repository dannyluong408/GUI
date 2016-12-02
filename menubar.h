#pragma once

#include <QtWidgets>
#include <dragpushbutton.h>

class Menubar: public QFrame
{
    Q_OBJECT
    public:
        Menubar(QWidget *parent);
    public slots:
        void resizeMe(QSize newSize);

    private slots:
        void toggleThis();

    signals:
        void openMenu();

    private:
        QPushButton *menuButton[5];

};
