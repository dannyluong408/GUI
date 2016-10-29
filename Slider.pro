#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T04:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Slider
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myopenglwidget.cpp \
    dragwidget.cpp

HEADERS  += mainwindow.h \
    myopenglwidget.h \
    dragwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    customSlider.qml

RESOURCES += \
    resources.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/draganddrop/draggableicons
INSTALLS += target
