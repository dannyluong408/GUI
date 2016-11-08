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

    signals:
        void openThis(QString name);

    private:
        QFrame *mainFrame;
        QLabel *frameLabel;
        QWidget *layoutFrame;
        QVBoxLayout *mainLayout;
        QPushButton *options[8];
};



#endif // GAMEMENU_H
