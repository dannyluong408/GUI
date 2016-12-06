#pragma once


#include <QApplication>
#include <QtWidgets>



class Application: public QApplication
{
    Q_OBJECT
    public:
        Application(int &argc, char **argv);
        void dragEnterEvent(QDragEnterEvent *event);
};
