#pragma once

#include <QtWidgets>
#include "GUI/keybindialog.hpp"
#include <cassert>

#define KEYBINDCOUNT 73

#define MOVE_BINDS 7
#define COMBAT_BINDS 1
#define TARGET_BINDS 30
#define CAMERA_BINDS 3
#define ACTION_PRIMARY_BINDS 10
#define ACTION_SECONDARY_BINDS 10
#define INTERFACE_BINDS 8
#define CHAT_BINDS 3
#define MISC_BINDS 1

#define MOVE_BINDS_RANGE MOVE_BINDS
#define COMBAT_BINDS_RANGE MOVE_BINDS_RANGE+COMBAT_BINDS
#define TARGET_BINDS_RANGE COMBAT_BINDS_RANGE+TARGET_BINDS
#define CAMERA_BINDS_RANGE TARGET_BINDS_RANGE+CAMERA_BINDS
#define ACTION_PRIMARY_BINDS_RANGE CAMERA_BINDS_RANGE+ACTION_PRIMARY_BINDS
#define ACTION_SECONDARY_BINDS_RANGE ACTION_PRIMARY_BINDS_RANGE+ACTION_SECONDARY_BINDS
#define INTERFACE_BINDS_RANGE ACTION_SECONDARY_BINDS_RANGE+INTERFACE_BINDS
#define CHAT_BINDS_RANGE INTERFACE_BINDS_RANGE+CHAT_BINDS
#define MISC_BINDS_RANGE CHAT_BINDS_RANGE+MISC_BINDS

#if KEYBINDCOUNT != MISC_BINDS_RANGE
    #error "KEYBINDCOUNT != MISC_BINDS_RANGE"
#endif

class KeybindMenu: public QFrame
{
    Q_OBJECT
    public:
        KeybindMenu(QWidget *parent);
        void updateBind(QKeySequence newKeybind, const unsigned int num);
        void copyShortcuts(QShortcut *copyshort[]);
        //void updateShortcut(QKeySequence keyseq);
        void updateText(const unsigned int num);

    public slots:
        void updateKeybinds(QString *shortcuts);
        void setBindMain(int num);
        void setBindBackup(int num);
        void newBindRecv(QKeySequence newKeybind, const unsigned int num);
        void resizeMe(QSize newSize);

    signals:
        void disableShortcuts();
        void enableShortcuts();
        void newBindSend(QKeySequence newKeybind, const unsigned int num);
        void defaultBinds();
        //void removeBinds();
        void saveBinds();

    private:
        QGridLayout *gridLayout;
        QVBoxLayout *mainLayout, *secondFrameVLayout[4];
        QFrame *mainFrame,*secondFrame,*secondFrameV[4];
        QHBoxLayout *secondLayout;

        QCheckBox *secondFrameCheckbox[2];
        QPushButton *secondFrameButtons[3];

        QPushButton *keybind[KEYBINDCOUNT], *keybindBackup[KEYBINDCOUNT];

        QLabel *keybindDesc[KEYBINDCOUNT];
        QLabel *sectionHeader[8], *header[3];

        QScrollArea *scrollArea;
        QSignalMapper *keybindMapperMain, *keybindMapperBackup;
        QShortcut **shortcuts;

        /*total rows
        1 + 0  = 1  header
        1 + 7  = 8  move
        1 + 1  = 2  combat
        1 + 30 = 31 target
        1 + 3  = 4  camera
        1 + 20 = 21 action
        1 + 8  = 9  interface
        1 + 3  = 4  chat
        1 + 1  = 2  misc
               = 82 rows , 73 buttons

        0-6 = move
        7 = combat
        8-37 = targeting
        38-40 = camera
        41-60 = action
        61-68 = interface
        69-71 = chat
        72 = misc
        */



};
