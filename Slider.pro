#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T04:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Slider
TEMPLATE = app

DEFINES += NX_USE_ASSETS ASSET_USE_GL DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    myopenglwidget.cpp \
    dragwidget.cpp \
    dragpushbutton.cpp \
    actionbar.cpp \
    bufficon.cpp \
    buffframe.cpp \
    unitframe.cpp \
    progressbar.cpp \
    chatbox.cpp \
    menubar.cpp \
    popupframe.cpp \
#    modules/buffs_ext.cpp \
#    modules/spell_module.cpp \
#    nx_src/nx_asset.c

HEADERS  += mainwindow.h \
    myopenglwidget.h \
    dragwidget.h \
    dragpushbutton.h \
    actionbar.h \
    bufficon.h \
    buffframe.h \
    unitframe.h \
    progressbar.h \
    chatbox.h \
    menubar.h \
    popupframe.h \
#    modules/buffs_module.h \
#    modules/spell_module.h \
#    nx_include/spell_list.h \
#    nx_include/nx_asset.h \
#    nx_include/nx_error.h \
#    nx_include/nx_timing.h

FORMS    += mainwindow.ui

DISTFILES +=           

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/libs/ -lassimp

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/assimp.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libassimp.a
