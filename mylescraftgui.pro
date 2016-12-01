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

TARGET = mylescraft
TEMPLATE = app


DEFINES += NX_USE_ASSETS ASSET_USE_GL DEBUG USING_QT

SOURCES += main.cpp\
        mainwindow.cpp \
    dragwidget.cpp \
    dragpushbutton.cpp \
    actionbar.cpp \
    bufficon.cpp \
    unitframe.cpp \
    progressbar.cpp \
    menubar.cpp \
	\
    modules/buffs_ext.cpp \
    modules/spell_module.cpp \
	modules/util.cpp \
	\
    nx_src/nx_asset.cpp \
    nx_src/nx_error.c \
    nx_src/nx_profiling.c \
    nx_src/nx_timing.c \
	nx_src/nx_deferred_processing.cpp \
	\
    gamemenu.cpp \
    spellbook.cpp \
    guildframe.cpp \
    options.cpp \
    playerbuffframe.cpp \
    targetbuffframe.cpp \
    partyframe.cpp \
    honorframe.cpp \
    chatframe.cpp \
    textedit.cpp \
    keybindmenu.cpp \
    keybinddialog.cpp \
    guildframe2.cpp

HEADERS  += mainwindow.h \
    dragwidget.h \
    dragpushbutton.h \
    actionbar.h \
    bufficon.h \
    unitframe.h \
    progressbar.h \
    menubar.h \
    modules/buffs_module.h \
    modules/spell_module.h \
    nx_include/spell_list.h \
    nx_include/nx_asset.h \
    nx_include/nx_error.h \
    nx_include/nx_timing.h \
    nx_include/nx_profiling.h \
    spellbook.h \
    guildframe.hpp \
    options.hpp \
    playerbuffframe.hpp \
    targetbuffframe.hpp \
    partyframe.hpp \
    honorframe.hpp \
    chatframe.hpp \
    textedit.hpp \
    keybindmenu.hpp \
    miscenum.hpp \
    keybindialog.hpp \
    gamemenu.hpp \
    guildframe2.hpp

FORMS    += mainwindow.ui

DISTFILES +=           

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/libs/ -lassimp

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/assimp.a -static
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libassimp.a
