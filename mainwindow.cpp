#include "mainwindow.h"
#include <QOpenGLFunctions>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);
    setFormat(format);
    context  = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);
    openGLFunctions = context->functions();
    rotation = 0;
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    //loadVertex(meshData, "teapot.obj");

    CreateVertexBuffer();
    CompileShaders();

    glEnable(GL_DEPTH_TEST);
    //resizeGL(this->width(), this->height());
}

void MainWindow::resizeGL(int w, int h)
{
}

void MainWindow::CreateVertexBuffer()
{
    // 创建含有3个顶点的顶点数组
    Vector3f Vertices[3];
    // 三角形的三个顶点位置
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

    // 创建缓冲器
    glGenBuffers(1, &VBO);
    // 绑定GL_ARRAY_BUFFER缓冲器
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 绑定顶点数据
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

}

void MainWindow::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    // Resetear transformaciones
    glLoadIdentity();


   // glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 开启顶点属性
   // glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //  禁用顶点数据
    glDisableVertexAttribArray(0);


    glFlush();
      this->makeCurrent();

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //resizeGL(this->width(), this->height());

    this->update();
}

void MainWindow::PaintEvent(QPaintEngine *event)
{
    paintGL();
}


