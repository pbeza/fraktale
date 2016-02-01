#include <qdebug.h>
#include "myglwidget.h"

/*
 * Learn more:
 * - http://doc.qt.io/qt-5.5/qopenglwidget.html#details
 * - http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html
 */

Ui::MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{ }

void Ui::MyGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // ...
    qDebug() << "test";
}

void Ui::MyGLWidget::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings:
    //m_projection.setToIdentity();
    //m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    // ...
}

void Ui::MyGLWidget::paintGL()
{
    // Draw the scene:
    glClear(GL_COLOR_BUFFER_BIT);
    // ...
}
