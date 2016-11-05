#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H



#pragma once

#include <QtWidgets>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL()
    {
        initializeOpenGLFunctions();
        glClearColor();
    }

    void resizeGL(int w, int h)
    {
        // Update projection matrix and other size related settings:
        m_projection.setToIdentity();
        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
        ...
    }

    void paintGL()
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        glClear(GL_COLOR_BUFFER_BIT);
        ...
    }

};
#endif // MYOPENGLWIDGET_H
