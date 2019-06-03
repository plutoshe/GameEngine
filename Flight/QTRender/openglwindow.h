#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H


#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

    virtual void Render(QPainter *painter);
    virtual void Render();

    virtual void Initialize();
    int frame;
    void setAnimating(bool animating);
    virtual void Update();
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;

    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
public slots:
    void renderLater();
    virtual void renderNow();


};
#endif // OPENGLWINDOW_H
