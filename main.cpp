#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "dragwidget.h"
#include <qglobal.h>
#include <QTime>

int main(int argc, char *argv[])
{

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    QApplication a(argc, argv);
    a.setStyle("fusion");
    a.setOverrideCursor(QCursor(QPixmap(":/ui/images/cursor_normal.png"),0,0));

    MainWindow w;
    //w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    //w.showMaximized();

    w.show();


    return a.exec();
}
