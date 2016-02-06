#include <vector>
#include <QMouseEvent>
#include <QDebug>
#include "myglwidget.h"

/*
 * Learn more:
 * - http://doc.qt.io/qt-5.5/qopenglwidget.html#details
 * - http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html
 */

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

Ui::MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    vndata = {
        0.1, 0.9, 0.0,
        0.9, 0.9, 0.0,
        0.1, 0.1, 0.0
    };
}

void Ui::MyGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.

    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, VERTEX_SHADER_PATH.c_str());
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, FRAGMENT_SHADER_PATH.c_str());
    m_program.bindAttributeLocation("vertex", 0);
    if (!m_program.link())
        qDebug() << "Linking OpenGL program has failed!";
    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    m_mvpMatrixLoc = m_program.uniformLocation("mvpMatrix");

    // Setup Vertex Array Object (VAO).

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup Vertex Buffer Object (VBO).

    m_logoVbo.create();
    if (!m_logoVbo.bind())
            qDebug() << "Binding OpenGL program has failed!";
    m_logoVbo.allocate(&vndata[0], vndata.size() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.

    if (!m_logoVbo.bind())
        qDebug() << "Binding OpenGL program has failed!";
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    m_logoVbo.release();

    // Our camera never changes in this example.

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -2);

    m_program.release();
}

void Ui::MyGLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 1000.0f);
}

void Ui::MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - m_xRot / 16.0f, 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    m_program.setUniformValue(m_mvpMatrixLoc, m_proj * m_camera * m_world);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program.release();
}

void Ui::MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void Ui::MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
}

void Ui::MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void Ui::MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void Ui::MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void Ui::MyGLWidget::updateVertices()
{
    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    if (!m_logoVbo.bind())
            qDebug() << "Binding OpenGL program has failed!";
    m_logoVbo.write(0, &vndata[0], vndata.size() * sizeof(GLfloat));
}
