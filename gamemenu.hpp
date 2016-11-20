#ifndef GAMEMENU_H
#define GAMEMENU_H

#pragma once


#include <QtWidgets>


class GameMenu : public QFrame
{
    Q_OBJECT
    public:
        GameMenu(QWidget *parent);

    public slots:
        void openOption();
        void resizeMe(QSize newSize);

    signals:
        void openThis(QString name);

    private:
        QLabel *frameLabel;
        QFrame *buttonFrame;
        QVBoxLayout *mainLayout, *buttonLayout;
        QPushButton *options[5];
};



#endif // GAMEMENU_H
