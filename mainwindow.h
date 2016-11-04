#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "actionbar.h"



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

private slots:
    void castSpell(int buttonPos);
    void login();

signals:
    void newSize(QSize newSize);

private:
    //bool eventFilter(QObject *obj, QEvent *event);
    Ui::MainWindow *ui;
    QWidget *loginScreen;
    ActionBar *actionBar[2];
    int numBars;
};

#endif // MAINWINDOW_H
