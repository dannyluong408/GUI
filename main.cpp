#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "dragwidget.h"
#include <qglobal.h>
#include <QTime>
#include "modules/util.h"
#include <nx_include/nx_localization.h>


int main(int argc, char *argv[]) {
    if (mc_util_init(argc, argv)) return -1;

    // this isn't supposed to be optional, but it can be for now.
    //if (mc_load_localization_file("resources/localization/english_strings")) return -2;
    mc_load_localization_file("resources/localization/english_strings");

    QApplication a(argc, argv);
    a.setStyle("fusion");


    MainWindow w;
    w.setWindowFlags(Qt::CustomizeWindowHint |
                     Qt::WindowMinimizeButtonHint |
                     Qt::WindowMaximizeButtonHint |
                     Qt::WindowCloseButtonHint);
    //w.showMaximized();

    w.show();

    a.exec();
    mc_util_exit();
    nx_localization_exit();
    return 0;
}
