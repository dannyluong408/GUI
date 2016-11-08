#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "actionbar.h"
#include <QHostInfo>


namespace Ui {
class MainWindow;
}

class PiecesList;
class PuzzleWidget;
class QListWidgetItem;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadImage(const QString &path);
    void resizeEvent(QResizeEvent *event);


public slots:
    void test(QString name);

private slots:
    void castSpell(int buttonPos);
    void login();
    void update();
    void lookedUp(const QHostInfo &host);

signals:
    void newSize(QSize newSize);
    void toggleSpellbook();

private:
    void keyPressEvent(QKeyEvent *event);
    Ui::MainWindow *ui;
    QWidget *loginScreen;
    ActionBar *actionBar[2];
    int numBars;
    QTimer timer;
};

#endif // MAINWINDOW_H
