#include "keybindialog.hpp"

KeybindDialog::KeybindDialog(QWidget *parent)
    : QFrame(parent)
{
    setGeometry(150,150,150,150);
    setObjectName("keybindDialog");
    setStyleSheet("border: 2px solid black;"
                  "background-color: white;");
    info = new QLabel(this);
    info->resize(150,150);
    info->setText("Press a Key Combination! Press (ESC) to cancel!");
    info->setAlignment(Qt::AlignCenter);
    info->setWordWrap(true);
    num = -1;
    count = 0;
    grabKeyboard();
    show();
}

//possibly use QKeySequenceEdit in the future but probably not
void KeybindDialog::keyReleaseEvent(QKeyEvent *event){
    if(event->modifiers() & Qt::ControlModifier){
        qDebug() << "MCtrl";
        keyPress.append("Ctrl+");
    }
    if(event->modifiers() & Qt::ShiftModifier){
        qDebug() << "MShift";
        keyPress.append("Shift+");
    }
    if(event->modifiers() & Qt::AltModifier){
        qDebug() << "MAlt";
        keyPress.append("Alt+");
    }

    switch (event->key()){
        case Qt::Key_unknown:{
            qDebug() << "Unknown Key";
            event->ignore();
            break;
        }
        case Qt::Key_Escape:{
            qDebug() << "Cannot bind escape!";
            event->ignore();
            delete(this);
            break;
        }
        case Qt::Key_Control:{
            qDebug() << "KCtrl";
            keyPress.append("Ctrl+");
            break;
        }
        case Qt::Key_Shift:{
            qDebug() << "KShift";
            keyPress.append("Shift+");
            break;
        }
        case Qt::Key_Alt:{
            qDebug() << "KAlt";
            keyPress.append("Alt+");
            break;
        }
        default:{
            qDebug() << "Just a Key Detected:" << QKeySequence(event->key()).toString();
            parseKey(keyPress + QKeySequence(event->key()).toString());
            return;
        }
    }
    info->setText(keyPress);
    return;
}

void KeybindDialog::parseKey(QString key){
    int size;
    //qDebug() << "Before Split:" << key;
    QStringList query = key.split('+');
    //qDebug() << "After Split:" << query;
    size = query.size();
    query.removeDuplicates();
    if (size != query.size()){
        qDebug() << "Bad Combo!";
        info->setText("Bad Key Combo! Try Again. Press (ESC) to cancel!");
        keyPress = "";
        return;
    }
    else{
        //qDebug() << key;
        emit newBind(QKeySequence(key),num);
        delete(this);
        return;
    }
}

