#include "GUI/mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "GUI/dragwidget.h"
#include <qglobal.h>
#include <QTime>
#include <modules/game.h>
#include <modules/util.h>
#include <nx_include/nx_localization.h>

MainWindow *mainwindow;
Game game;

int main(int argc, char *argv[]) {
    if (mc_util_init(argc, argv)) return -1;

    // this isn't supposed to be optional, but it can be for now.
    //if (mc_load_localization_file("resources/localization/english_strings")) return -2;
    //mc_load_localization_file("resources/localization/english_strings");

    QApplication a(argc, argv);
    a.setStyle("fusion");
    a.setQuitOnLastWindowClosed(false);

    mainwindow = new MainWindow;
    mainwindow->setWindowFlags(Qt::CustomizeWindowHint |
                     Qt::WindowMinimizeButtonHint |
                     Qt::WindowMaximizeButtonHint |
                     Qt::WindowCloseButtonHint);
    //w.showMaximized();

    mainwindow->show();
    while (!game.quit()) {
        a.sendPostedEvents();
        a.processEvents();
        game.step();
    }
    mc_util_exit();
    nx_localization_exit();
    return 0;
}
