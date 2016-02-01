#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

namespace Ui
{

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    MyGLWidget(QWidget *parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};

}

#endif // MYGLWIDGET_H
