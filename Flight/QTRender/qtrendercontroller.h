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
#ifdef _WIN32
    const char* pVSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.vs";
    const char* pFSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.fs";
#endif
#ifdef __APPLE__
     const char* pVSFileName = "/Users/plutoshe/Downloads/opengltest/shader.vs";
     const char* pFSFileName = "/Users/plutoshe/Downloads/opengltest/shader.fs";
#endif
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
#ifdef __APPLE__
        // ignore the header of ut8 file
        vertexShaderSource = vertexShaderSource.substr(3);
        fragmentShaderSource = fragmentShaderSource.substr(3);
#endif
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str());
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str());
        m_program->link();

        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);
        glClear(GL_COLOR_BUFFER_BIT);
        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            Engine::ObservingPointer<QTRenderComponent> r = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ListRenderComponent[i]);
            r->Initialize();
            r->CreateTexture();
        }
    }


    void file_reader(std::string file, std::string &result)
    {
        std::string line;
        std::ifstream myfile(file);
        result = "";
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
m_context->makeCurrent(this);
        if (needsInitialize) {
            initializeOpenGLFunctions();
            Initialize();
        }
Render();
m_context->swapBuffers(this);
    }

     void Render() override {
        glClearColor(0.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_program->bind();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glLoadIdentity();

        int posAttr = m_program->attributeLocation("Position");
        int texCoordAttr = m_program->attributeLocation("TexCoord");

        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            Engine::ObservingPointer<QTRenderComponent> r = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ListRenderComponent[i]);
            if (r) {
                r->posAttrLocation = posAttr;
                r->texCoordAttrLocation = texCoordAttr;
            }
            r->Render();
        }
        glFlush();
        //m_program->release();
    }

};

#endif
