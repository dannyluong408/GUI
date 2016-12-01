#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "dragwidget.h"
#include <qglobal.h>
#include <QTime>
#include "modules/util.h"

int main(int argc, char *argv[]) {
    if (mc_util_init(argc, argv)) return -1;

    QApplication a(argc, argv);
    a.setStyle("fusion");
    a.setOverrideCursor(QCursor(QPixmap(":/ui/images/cursor_normal.png"),0,0));

    MainWindow w;
    w.setWindowFlags(Qt::CustomizeWindowHint |
                     Qt::WindowMinimizeButtonHint |
                     Qt::WindowMaximizeButtonHint |
                     Qt::WindowCloseButtonHint);
    //w.showMaximized();

    w.show();
    a.exec();
    mc_util_exit();
    return 0;
}
