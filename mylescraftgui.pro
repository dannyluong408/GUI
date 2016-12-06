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
    GUI/mainwindow.cpp \
    GUI/dragwidget.cpp \
    GUI/dragpushbutton.cpp \
    GUI/actionbar.cpp \
    GUI/bufficon.cpp \
    GUI/unitframe.cpp \
    GUI/progressbar.cpp \
    GUI/menubar.cpp \
    modules/buffs_ext.cpp \
    modules/spell_module.cpp \
    nx_src/nx_localization.cpp \
    modules/util.cpp \
    modules/game.cpp \
    modules/user.cpp \
    modules/camera.cpp \
    nx_src/nx_asset.cpp \
    nx_src/nx_error.cpp \
    nx_src/nx_profiling.c \
    nx_src/nx_timing.c \
    nx_src/nx_deferred_processing.cpp \
    GUI/gamemenu.cpp \
    GUI/spellbook.cpp \
    GUI/options.cpp \
    GUI/playerbuffframe.cpp \
    GUI/targetbuffframe.cpp \
    GUI/partyframe.cpp \
    GUI/honorframe.cpp \
    GUI/chatframe.cpp \
    GUI/textedit.cpp \
    GUI/keybindmenu.cpp \
    GUI/keybinddialog.cpp \
    GUI/gamescreen.cpp \
    GUI/textbrowser.cpp \
    GUI/application.cpp \
    GUI/guildframe.cpp

HEADERS  += GUI/mainwindow.h \
    GUI/dragwidget.h \
    GUI/dragpushbutton.h \
    GUI/actionbar.h \
    GUI/bufficon.h \
    GUI/unitframe.h \
    GUI/progressbar.h \
    GUI/menubar.h \
    modules/buffs_module.h \
    modules/spell_module.h \
    nx_include/spell_list.h \
    nx_include/nx_asset.h \
    nx_include/nx_error.h \
    nx_include/nx_timing.h \
    nx_include/nx_profiling.h \
    GUI/spellbook.h \
    GUI/options.hpp \
    GUI/playerbuffframe.hpp \
    GUI/targetbuffframe.hpp \
    GUI/partyframe.hpp \
    GUI/honorframe.hpp \
    GUI/chatframe.hpp \
    GUI/textedit.hpp \
    GUI/keybindmenu.hpp \
    GUI/miscenum.hpp \
    GUI/keybindialog.hpp \
    GUI/gamemenu.hpp \
    GUI/gamescreen.hpp \
    GUI/textbrowser.hpp \
    nx_include/nx_localization.h \
    GUI/application.hpp \
    GUI/guildframe.hpp

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

unix|win32: LIBS += -L$$PWD/libs/ -lassimp

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/assimp.a -static
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libs/libassimp.a
