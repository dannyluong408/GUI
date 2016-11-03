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
    void resizeEvent(QResizeEvent *event);


public slots:

private slots:
    void castSpell(int buttonPos);

signals:
    void newSize(QSize newSize);

private:
    //bool eventFilter(QObject *obj, QEvent *event);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
