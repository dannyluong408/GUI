#ifndef ACTIONBAR_H
#define ACTIONBAR_H

#include <QtWidgets>
#include "dragpushbutton.h"

#define NUMBUTTONS 10

class QDragEnterEvent;
class QDropEvent;

class ActionBar : public QWidget
{
public:
    ActionBar(QWidget *parent = 0);
    void setMainBarHotkey();
    void setButtonSpell(uint32_t spellid, uint32_t buttonNum);
    uint32_t getButtonSpell(uint32_t buttonNum);

public slots:
    void resizeMe(QSize);

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
