#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


public slots:
    void printValues();

private slots:
    void castSpell(int buttonPos);
    void addButton(int button);

private:
    //bool eventFilter(QObject *obj, QEvent *event);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
