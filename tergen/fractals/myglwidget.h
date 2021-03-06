#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPoint>
#include <QMatrix4x4>

namespace Ui
{

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent);
    void updateVertices();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    const std::string VERTEX_SHADER_PATH = "../fractals/vertexshader.glsl";
    const std::string FRAGMENT_SHADER_PATH = "../fractals/fragmentshader.glsl";
    QPoint m_lastPos;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLBuffer m_Ibo;
    QOpenGLShaderProgram m_program;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_world;
    int m_mvpMatrixLoc;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    size_t vertex_count;

public:
    QMatrix4x4 m_camera;
    std::vector<GLfloat> vndata;
    std::vector<GLuint> index_data;
    QVector3D cameraPosition;
    GLenum drawMode = GL_TRIANGLE_STRIP;
};

}

#endif // MYGLWIDGET_H
