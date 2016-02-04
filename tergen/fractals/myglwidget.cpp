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
    // Set up the rendering context, load shaders and other resources, etc.

    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "../fractals/vertexshader.glsl");
    m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "../fractals/fragmentshader.glsl");
    m_program.bindAttributeLocation("vertex", 0);
    //m_program.bindAttributeLocation("normal", 1);
    if (!m_program.link())
        qDebug() << "Linking OpenGL program has failed!";

    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    m_projMatrixLoc = m_program.uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program.uniformLocation("mvMatrix");
    //m_normalMatrixLoc = m_program.uniformLocation("normalMatrix");
    //m_lightPosLoc = m_program.uniformLocation("lightPos");

    // Setup Vertex Array Object (VAO).

    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup Vertex Buffer Object (VBO).

    GLfloat vndata[] = {
        0.1, 0.1, 0.0,
        0.9, 0.9, 0.0,
        0.1, 0.9, 0.0
    };
    const int n = sizeof(vndata) / sizeof(GLfloat);
    m_logoVbo.create();
    if (!m_logoVbo.bind())
            qDebug() << "Binding OpenGL program has failed!";
    m_logoVbo.allocate(vndata, n * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.

    if (!m_logoVbo.bind())
        qDebug() << "Binding OpenGL program has failed!";
    glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_logoVbo.release();

    // Our camera never changes in this example.

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.

    //m_program.setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program.release();
}

void Ui::MyGLWidget::resizeGL(int w, int h)
{
    // Update projection matrix and other size related settings.
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void Ui::MyGLWidget::paintGL()
{
    // Draw the scene.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (/*m_xRot*/0 / 16.0f), 1, 0, 0);
    m_world.rotate(0 /*m_yRot*/ / 16.0f, 0, 1, 0);
    m_world.rotate(0 /*m_zRot*/ / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    m_program.setUniformValue(m_projMatrixLoc, m_proj);
    m_program.setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    //QMatrix3x3 normalMatrix = m_world.normalMatrix();
    //m_program.setUniformValue(m_normalMatrixLoc, normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program.release();
}

void Ui::MyGLWidget::mousePressEvent(QMouseEvent *event)
{
}

void Ui::MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
}
