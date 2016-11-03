#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "dragwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(QPixmap(":/ui/images/cursor_normal.png"),0,0));
    MainWindow w;
    //w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    //w.showMaximized();

    w.show();


    return a.exec();
}
