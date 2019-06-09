#include "openglwindow.h"

#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include <QtDebug>
OpenGLWindow::OpenGLWindow(QWindow *parent)
    : QWindow(parent)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow()
{
    delete m_device;
}
void OpenGLWindow::Render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void OpenGLWindow::Initialize()
{
}

void OpenGLWindow::Render()
{
    qDebug() << "openglwindow render";
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    Render(&painter);
}

void OpenGLWindow::renderLater()
{
    requestUpdate();
}
void OpenGLWindow::Update() {
    qDebug() << "in wrong update(openglwindow)";
    renderNow();
}
bool OpenGLWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        frame++;
        qDebug() << frame;
        //renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);
    if (!isExposed())
        return;
    qDebug("expose start");
    renderNow();
    qDebug("expose end");
}


void OpenGLWindow::renderNow()
{
    qDebug() <<"Render paher 1";
             if (!isExposed())
                 return;

             bool needsInitialize = false;

             if (!m_context) {
                 m_context = new QOpenGLContext(this);
                 m_context->setFormat(requestedFormat());
                 m_context->create();

                 needsInitialize = true;

             }
//    qDebug() <<"Render paher 11" << m_app;
    m_context->makeCurrent(this);
//    qDebug() <<"Render paher 110" << m_app;
             if (needsInitialize) {
                 initializeOpenGLFunctions();
                 Initialize();
             }
    Render();
    m_context->swapBuffers(this);
}

void OpenGLWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}
