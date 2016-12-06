#include "GUI/application.hpp"






Application::Application(int &argc, char **argv)
    : QApplication(argc,argv)
{

}


void Application::dragEnterEvent(QDragEnterEvent *event){
    qDebug() << "Test";
    event->accept();
}
