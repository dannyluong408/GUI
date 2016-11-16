#ifndef KEYBINDMENU_HPP
#define KEYBINDMENU_HPP

#pragma once

#include <QtWidgets>
#include "keybindialog.hpp"

#define KEYBINDCOUNT 73

class KeybindMenu: public QFrame
{
    Q_OBJECT
    public:
        KeybindMenu(QWidget *parent);

    public slots:
        void updateKeybinds(QString *shortcuts);
        void setBindMain(int num);
        void setBindBackup(int num);

    signals:
        void disableShortcuts();
        void enableShortcuts();

    private:
        QGridLayout *mainLayout;
        QFrame *mainFrame,*secondFrame;
        QPushButton *moveKeybind[7],*moveKeybindBackup[7],
                    *combatKeybind,*combatKeybindBackup,
                    *targetingKeybind[30],*targetingKeybindBackup[30],
                    *cameraKeybind[3],*cameraKeybindBackup[3],
                    *actionPrimaryButtonKeybind[10],*actionPrimaryButtonKeybindBackup[10],
                    *actionSecondaryButtonKeybind[10],*actionSecondaryButtonKeybindBackup[10],
                    *interfaceKeybind[8],*interfaceKeybindBackup[8],
                    *chatKeybind[3],*chatKeybindBackup[3],
                    *miscKeybind,*miscKeybindBackup;

        QLabel *sectionHeader[8], *header[3],
               *moveKeybindDesc[7],
               *combatKeybindDesc,
               *targetingKeybindDesc[30],
               *cameraKeybindDesc[3],
               *actionPrimaryButtonKeybindDesc[10],
               *actionSecondaryButtonKeybindDesc[10],
               *interfaceKeybindDesc[8],
               *chatKeybindDesc[3],
               *miscKeybindDesc;

        const QString moveKeybindDescName[7] = {"Move Forward",
                                          "Move Backward",
                                          "Turn Left",
                                          "Turn Right",
                                          "Move Left",
                                          "Move Right",
                                          "Jump"},
                combatKeybindDescName = "Toggle Attack",
                targetingKeybindDescName[30] = {"Target Nearest Enemy","Target Previous Enemy",
                                                "Target Nearest Enemy Player","Target Previous Enemy Player",
                                                "Target Nearest Friendly Player","Target Previous Friendly Player",
                                                "Target Self","Target Party Member 1","Target Party Member 2","Target Party Member 3","Target Party Member 4",
                                                "Target Pet","Target Party Pet 1","Target Party Pet 2","Target Party Pet 3","Target Party Pet 4",
                                                "Assist Target","Toggle Nameplates","Toggle Friendly Nameplates","Set Focus",
                                                "Focus Arena 1","Focus Arena 2","Focus Arena 3","Focus Arena 4","Focus Arena 5",
                                                "Target Arena 1","Target Arena 2","Target Arena 3","Target Arena 4","Target Arena 5"},
                cameraKeybindDescName[3] = {"Camera Zoom In","Camera Zoom Out","Camera Reverse"},
                actionPrimaryButtonKeybindDescName[10] = {"Main Button 0","Main Button 1","Main Button 2","Main Button 3","Main Button 4",
                                                   "Main Button 5","Main Button 6","Main Button 7","Main Button 8","Main Button 9"},
                actionSecondaryButtonKeybindDescName[10] = {"Secondary Button 0","Secondary Button 1","Secondary Button 2","Secondary Button 3","Secondary Button 4",
                                                   "Secondary Button 5","Secondary Button 6","Secondary Button 7","Secondary Button 8","Secondary Button 9"},
                interfaceKeybindDescName[8] = {"Toggle Spellbook","Toggle Clan","Toggle Honor","Open Main Menu",
                                               "Toggle Char Menu","Toggle Macro","Toggle Social","Toggle Map"},
                chatKeybindDescName[3] = {"Open Chat","Reply Whisper","Re-Whisper"},
                miscKeybindDescName = "Take Screenshot";

        QScrollArea *scrollArea;
        QSignalMapper *keybindMapperMain, *keybindMapperBackup;

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
        */

};

#endif // KEYBINDMENU_HPP
