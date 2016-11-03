#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include "dragwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOverrideCursor(QCursor(QPixmap(":/ui/images/cursor_normal.png")));
    MainWindow w;
    //w.setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    //w.showMaximized();
    w.show();

//    QWidget mainWidget;
//    QHBoxLayout *horizontalLayout = new QHBoxLayout(&mainWidget);
//    horizontalLayout->addWidget(new DragWidget);
//    horizontalLayout->addWidget(new DragWidget);

//    mainWidget.setWindowTitle(QObject::tr("Draggable Icons"));
//    mainWidget.show();

    return a.exec();
}
