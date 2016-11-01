#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <QtWidgets>
#include "actionbar.h"
#include "dragpushbutton.h"

#define NUMBUTTONS 10

class QDragEnterEvent;
class QDropEvent;

class ActionBar : public QWidget
{
public:
    ActionBar(QWidget *parent = 0);
    void setMainBarHotkey();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QButtonGroup *buttonGroup;
    PushButton *buttonSet[NUMBUTTONS];
};


#endif // ACTIONBAR_H
