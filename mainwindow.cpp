#include "mainwindow.h"
#include <QOpenGLFunctions>

MainWindow::MainWindow(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    // for opengl3+
    // format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(2,1);
    setFormat(format);
    context  = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);
    openGLFunctions = context->functions();

   // QTimer *timer = new QTimer(this);

  //  connect(timer, SIGNAL(timeout()), this, SLOT(UpdateAnimation()));

    //timer->start(100);
    rotation = 0;
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();
    loadVertex(meshData, "teapot.obj");

    CreateVertexBuffer();
    CompileShaders();

    glEnable(GL_DEPTH_TEST);
    //resizeGL(this->width(), this->height());
}

void MainWindow::resizeGL(int w, int h)
{
//    glMatrixMode(GL_PROJECTION);
   // glEnable(GL_BLEND);
//    glLoadIdentity();
//    glViewport(0,0,w,h);
//    qreal aspectratio = qreal(w)/qreal(h);
//    glOrtho(-1 * aspectratio, 1 * aspectratio, -1,1,1,-1);

//    // set viewport
//    glViewport(0, 0, w, h);
//    qreal aspectratio = qreal(w) / qreal(h);
//    // Initialize Projection Matrix

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();

//    //
//    // Initialize Model View Matrix
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

//    gluPerspective(75, aspectratio, 0.1, 4000000000);

}

void MainWindow::CreateVertexBuffer()
{
    // 创建含有3个顶点的顶点数组
//    Vector3f Vertices[3];
//    // 三角形的三个顶点位置
//    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
//    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
//    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
////    GLfloat vertices[]  = {
////         .5f, .5f, .5f,  -.5f, .5f, .5f,  -.5f,-.5f, .5f,  .5f,-.5f, .5f, // v0,v1,v2,v3 (front)
////         .5f, .5f, .5f,   .5f,-.5f, .5f,   .5f,-.5f,-.5f,  .5f, .5f,-.5f, // v0,v3,v4,v5 (right)
////         .5f, .5f, .5f,   .5f, .5f,-.5f,  -.5f, .5f,-.5f, -.5f, .5f, .5f, // v0,v5,v6,v1 (top)
////        -.5f, .5f, .5f,  -.5f, .5f,-.5f,  -.5f,-.5f,-.5f, -.5f,-.5f, .5f, // v1,v6,v7,v2 (left)
////        -.5f,-.5f,-.5f,   .5f,-.5f,-.5f,   .5f,-.5f, .5f, -.5f,-.5f, .5f, // v7,v4,v3,v2 (bottom)
////         .5f,-.5f,-.5f,  -.5f,-.5f,-.5f,  -.5f, .5f,-.5f,  .5f, .5f,-.5f  // v4,v7,v6,v5 (back)
////    };
//    // 创建缓冲器
//    glGenBuffers(1, &VBO);
//    // 绑定GL_ARRAY_BUFFER缓冲器
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    // 绑定顶点数据
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    const int num = meshData.NV();
        Vector3f Vertices[3241];
        // 将点置于屏幕中央
        cy::Point3f *v = meshData.GetVerticesArray();
        for (int i = 0; i < num; i++)
            Vertices[i] = Vector3f(v[i].x, v[i].y, v[i].z);

        printf("%d", sizeof(Vertices));

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
    glClearColor(1.0f, 0.0f, 0.0f, 0.f);
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

//void MainWindow::UpdateAnimation()
//{
//    rotation += 10;
//    this->update();
//}
