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
    //, m_logoVbo(QOpenGLBuffer::VertexBuffer)
    , m_Ibo(QOpenGLBuffer::IndexBuffer)
{
    vndata = {
        0.1, 0.9, 0.0,
        0.9, 0.9, 0.0,
        0.1, 0.1, 0.0
    };

    index_data = {
        0, 1, 2
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

    //m_vao.create();
    //m_vao.bind();

    // Setup Vertex Buffer Object (VBO).

    m_logoVbo.create();
    if (!m_logoVbo.bind())
        qDebug() << "Binding vertex position buffer has failed!";
    m_logoVbo.allocate(&vndata[0], vndata.size() * sizeof(GLfloat));
    //m_logoVbo.setUsagePattern(QOpenGLBuffer::StaticDraw);

    // Store the vertex attribute bindings for the program.

    if (!m_logoVbo.bind())
        qDebug() << "Binding vertex position buffer has failed!";
    int vertexLocation = m_program.attributeLocation("vertex");
    m_program.enableAttributeArray(vertexLocation);
    m_program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, 0);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    m_logoVbo.release();

    m_Ibo.create();
    if (!m_Ibo.bind())
        qDebug() << "Binding index buffer has failed!";
    m_Ibo.allocate(&index_data[0], index_data.size() * sizeof(GLuint));
    //m_Ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_Ibo.release();

    m_camera.setToIdentity();
    m_camera.translate(0, 0, -2);
    m_xRot = 90;

    m_program.release();
    //m_vao.release();
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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - m_xRot / 16.0f, 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    //m_vao.bind();
    if (!m_program.bind())
        qDebug() << "Binding OpenGL program has failed!";
    m_program.setUniformValue(m_mvpMatrixLoc, m_proj * m_camera * m_world);
    if (!m_logoVbo.bind())
        qDebug() << "Binding vertex position buffer has failed!";
    if (!m_Ibo.bind())
        qDebug() << "Binding index buffer has failed!";

    glDrawElements(GL_TRIANGLE_STRIP, index_data.size(), GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_POINTS, index_data.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLE_STRIP, 0, index_data.size());

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
        qDebug() << "Binding vertex position buffer has failed!";
    m_logoVbo.allocate(&vndata[0], vndata.size() * sizeof(GLfloat));
    m_logoVbo.release();
    if (!m_Ibo.bind())
        qDebug() << "Binding index buffer has failed!";
    m_Ibo.allocate(&index_data[0], index_data.size() * sizeof(GLuint));
    m_Ibo.release();
}
