#pragma once

#include <QMainWindow>
#include <QHostInfo>
#include <QDebug>
#include <QtGlobal>
#include <time.h>
#include "GUI/miscenum.hpp"
#include <QFlags>
#include <cassert>
#include <QWidget>
#include <QTimer>
#include <QShortcut>
#include <QSignalMapper>
#include <QPushButton>
#include "GUI/application.hpp"

#define KEYBINDCOUNT 73

extern QApplication *a;
class ActionBar;
class UnitFrame;
class ActionBar;
class UnitFrame;
class PartyFrame;
class PlayerBuffFrame;
class TargetBuffFrame;
class ChatFrame;
class Menubar;
class SpellBook;
class GuildFrame2;
class HonorFrame;
class GameMenu;
class OptionsFrame;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadImage(const QString &path);
    void resizeEvent(QResizeEvent *event);
    void initDefaultKeybinds();
    void initDefaultActionbars();
    void initKeybinds();
    void loadActionBars();

    void handleIncomingBuff(uint32_t buffid, bool player, bool insert);
    void keyPressEvent(QKeyEvent *event);

    //keybind functions
    void movePlayer(int direction);
    void togglePane(int pane);

    void toggleAttack();
    void targetingBind(int target);
    void cameraBind(int option);
    void toggleChat();
    void whisper(int type);
    void screenshot();

    void wheelEvent(QWheelEvent *wevent);
    void mousePressEvent(QMouseEvent *mevent);

    void setCursorID(uint32_t id);
    uint32_t getCursorID();

public slots:
    void openOption(QString name);
    void disableShortcuts();
    void enableShortcuts();
    void newBindRecv(QKeySequence newKeybind, const int num);
    void saveKeybinds();
    void defaultKeybinds();
    void saveActionBars();
    void spellPickedUp(const uint32_t spellId);

private slots:
    void castSpell(int buttonPos);
    void login();
    void update();
    void lookedUp(const QHostInfo &host);
    //keybind slots
    void keybindSlot(int id);

signals:
    void newSize(QSize newSize);
    void toggleSpellbook();
    void pushKeybinds(QString *keybinds);

private:
    void initializeKeyBinds();
    //void keyPressEvent(QKeyEvent *event);
    Ui::MainWindow *ui;
    QTimer timer;

    //login stuff
    QWidget *loginScreen;
    QPushButton *loginButton;

    //core widgets
    ActionBar *actionBar[2];
    int numBars;
    UnitFrame *playerFrame,*targetFrame;
    PartyFrame *partyFrame;
    PlayerBuffFrame *playerBuff;
    TargetBuffFrame *targetBuff;
    ChatFrame *chatFrame;
    Menubar *menuBar;
    SpellBook *spellBook;
    GuildFrame2 *guildFrame;
    HonorFrame *honorFrame;
    GameMenu *gameMenu; //pops up when u hit esc
    OptionsFrame *optionsMenu; //pops up after u click options

    QString keybindString[73];
    QShortcut *shortcut[73];
    QSignalMapper *keybindMapper;

    uint32_t cursorID;
    double keybindVersion;
};

extern MainWindow *mainwindow;
