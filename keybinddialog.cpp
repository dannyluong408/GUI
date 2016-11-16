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
    info->setText("Press a Key Combination!");
    info->setAlignment(Qt::AlignCenter);
    grabKeyboard();
    show();
}


void KeybindDialog::keyReleaseEvent(QKeyEvent *event){
    QKeySequence keybind;
    if(event->modifiers() & Qt::ControlModifier &&
       event->modifiers() & Qt::ShiftModifier &&
       event->modifiers() & Qt::AltModifier){
        qDebug() << "Shift Control Alt Detected";
        keyPress.append("Shift+Ctrl+Alt");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier &&
            event->modifiers() & Qt::ControlModifier){
        qDebug() << "Shift Control Detected";
        keyPress.append("Shift+Ctrl+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier &&
            event->modifiers() & Qt::AltModifier){
        qDebug() << "Shift Alt Detected";
        keyPress.append("Shift+Alt+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::AltModifier &&
            event->modifiers() & Qt::ControlModifier){
        qDebug() << "Control Alt Detected";
        keyPress.append("Ctrl+Alt+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::ShiftModifier){
        qDebug() << "Shift Detected";
        keyPress.append("Shift+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::ControlModifier){
        qDebug() << "Control Detected";
        keyPress.append("Ctrl+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else if(event->modifiers() & Qt::AltModifier){
        qDebug() << "Alt Detected";
        keyPress.append("Alt+");
        qDebug() << QKeySequence(keyPress + event->key()).toString();
        delete(this);
        return;
    }

    else{
        if (event->text() == ""){
            if(event->key() == Qt::Key_unknown){
                qDebug() << "Unknown";
            }
            qDebug() << "Need a key with modifier for bind";
            delete(this);
            return;
        }
        qDebug() << "Just a Key Detected";
        qDebug() << QKeySequence(event->key()).toString();
        if(event->key() == Qt::Key_Escape){
            qDebug() << "Escaped";
            event->ignore();
        }
        delete(this);
        return;
    }
}

void KeybindDialog::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Escape){
        qDebug() << "Esc pressed down";
        event->ignore();
    }
}

void KeybindDialog::reject(){

}
