#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFramebufferObjectFormat>
#include <cmath>
#include "cyLib/cyTriMesh.h"
//#include <QtOpenGL>
//#include <gl/GLU.h>
class Vector3f {
public:
    float m_x, m_y, m_z;
    void Clear() { m_x = m_y = m_z = 0; }
    Vector3f() { Clear(); }
    void operator=(const Vector3f &b) {
        m_x = b.m_x;
        m_y = b.m_y;
        m_z = b.m_z;
    }
    Vector3f(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
    float Length() { return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));}
};

class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void resizeEvent(QResizeEvent *event);
    void PaintEvent(QPaintEngine *event);
    void CreateVertexBuffer();
    void loadVertex(cyTriMesh &trimesh, char* filename) {
        trimesh.LoadFromFileObj("teapot.obj");
    }
public slots:
    //void UpdateAnimation();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;
    GLuint VBO;
    float rotation;
};

#endif // MAINWINDOW_H
