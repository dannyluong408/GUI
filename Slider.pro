#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T04:01:08
#
#-------------------------------------------------

QT       += core gui
QT       += opengl \
    sql \
    network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Slider
TEMPLATE = app


DEFINES += NX_USE_ASSETS ASSET_USE_GL DEBUG

SOURCES += main.cpp\
        mainwindow.cpp \
    dragwidget.cpp \
    dragpushbutton.cpp \
    actionbar.cpp \
    bufficon.cpp \
    unitframe.cpp \
    progressbar.cpp \
    chatbox.cpp \
    menubar.cpp \
    modules/buffs_ext.cpp \
    modules/spell_module.cpp \
    nx_src/nx_asset.cpp \
    nx_src/nx_error.c \
    nx_src/nx_profiling.c \
    nx_src/nx_timing.c \
    gamemenu.cpp \
    spellbook.cpp \
    guildframe.cpp \
    options.cpp \
    playerbuffframe.cpp \
    targetbuffframe.cpp \
    partyframe.cpp

HEADERS  += mainwindow.h \
    dragwidget.h \
    dragpushbutton.h \
    actionbar.h \
    bufficon.h \
    unitframe.h \
    progressbar.h \
    chatbox.h \
    menubar.h \
    modules/buffs_module.h \
    modules/spell_module.h \
    nx_include/spell_list.h \
    nx_include/nx_asset.h \
    nx_include/nx_error.h \
    nx_include/nx_timing.h \
    nx_include/nx_profiling.h \
    gamemenu.h \
    spellbook.h \
    guildframe.hpp \
    options.hpp \
    playerbuffframe.hpp \
    targetbuffframe.hpp \
    partyframe.hpp

FORMS    += mainwindow.ui

DISTFILES +=           

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/libs/ -lassimp

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/assimp.a -static
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libassimp.a
