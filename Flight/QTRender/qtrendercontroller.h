#ifndef QT_RENDER_CONTROLLER
#define QT_RENDER_CONTROLLER

#include <QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include "Engine/Engine.h"
#include "openglwindow.h"
#include "qtrendercomponent.h"
#include <fstream>

class QTRenderController : public OpenGLWindow, public RenderController
{
    Q_OBJECT
public:
    QOpenGLShaderProgram *m_program;
    QGuiApplication* m_app;
    int screenHeight = 600, screenWidth = 800;
    int sampleRate = 16;
    int m_test = 0;
    QTRenderController() {}
    QTRenderController(QGuiApplication *app) { m_app = app;}
    ~QTRenderController() {}
    const char* pVSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.vs";
    const char* pFSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.fs";

    void CreateAWindow() {
        QSurfaceFormat format;
        format.setSamples(sampleRate);
        qDebug() << "phase start: Render start";
        setFormat(format);
        resize(screenWidth, screenHeight);
        show();
    }

    void Start() {
        if (!isExposed())
            return;
    }
    void test() { qDebug() << "in qt render";}

    void Initialize()
    {
        qDebug() << "qt render controller initialization";
        initializeOpenGLFunctions();
        m_program = new QOpenGLShaderProgram(this);
        std::string vertexShaderSource, fragmentShaderSource;
        file_reader(pVSFileName,  vertexShaderSource);
        file_reader(pFSFileName, fragmentShaderSource);
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str());
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str());
        m_program->link();

        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);
        qDebug() <<"Render paher 2" << m_app;
        glClear(GL_COLOR_BUFFER_BIT);
        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            Engine::ObservingPointer<QTRenderComponent> r = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ListRenderComponent[i]);
            qDebug() <<"Render paher 3" << r;
            r->Initialize();
            r->CreateTexture();
        }
    }


    void file_reader(std::string file, std::string &result)
    {
        std::string line;
        std::ifstream myfile(file);
        if (myfile.is_open())
        {
            while (myfile.good())
            {
                getline(myfile, line);
                result += line + "\n";
            }
            myfile.close();
        }
        else
        {
            std::cout << "Unable to open file";
        }
    }


    void Update() override {
        RenderNowa();
    }
public slots:
    virtual void RenderNowa() {
        qDebug() << "NIUBIAO";
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

     void Render() {
        glClearColor(0.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        qDebug() <<"Render paher 1" << m_app;

        qDebug() <<"Render paher 3" << m_app;
        m_program->bind();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glLoadIdentity();

        int posAttr = m_program->attributeLocation("Position");
        int texCoordAttr = m_program->attributeLocation("TexCoord");

        qDebug() << "render size: " << ListRenderComponent.size();
        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            Engine::ObservingPointer<QTRenderComponent> r = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ListRenderComponent[i]);
            if (r) {
                qDebug() << "tt: ";
                r->posAttrLocation = posAttr;
                r->texCoordAttrLocation = texCoordAttr;
            }
            qDebug() << "rr: " << r->posAttrLocation;
               qDebug() << "rr: " << r->texCoordAttrLocation;
            r->Render();
        }
qDebug() << "p1";
        glFlush();
        //m_program->release();
        qDebug() << "p21";
    }

};

#endif
