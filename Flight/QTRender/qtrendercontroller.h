    #ifndef QT_RENDER_CONTROLLER
#define QT_RENDER_CONTROLLER

#include <QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include "Engine/Engine.h"
#include "openglwindow.h"
#include "qtrendercomponent.h"
#include <fstream>

class QTRenderController : public RenderController, public OpenGLWindow
{
public:
    QOpenGLShaderProgram *m_program;
    QGuiApplication* m_app;
    int m_test = 0;
    QTRenderController() {}
    QTRenderController(QGuiApplication *app) { m_app = app;}
    ~QTRenderController() {}
    const char* pVSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.vs";
    const char* pFSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.fs";
    void Start() {
        QSurfaceFormat format;
        format.setSamples(16);
        qDebug() << "phase start: Render start";
        setFormat(format);
        resize(640, 480);
        show();
        //Initialize();
    }
    void test() { qDebug() << "in qt render";}
    void Initialize()
    {
         //initializeGLFunctions();
        qDebug() << "qt render controller initialization";
        initializeOpenGLFunctions();
        m_program = new QOpenGLShaderProgram(this);
        std::string vertexShaderSource, fragmentShaderSource;
        file_reader(pVSFileName,  vertexShaderSource);
        file_reader(pFSFileName, fragmentShaderSource);
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str());
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str());
        m_program->link();

//         void TriangleWindow::initialize()
// {
//     m_program = new QOpenGLShaderProgram(this);
//     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
//     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
//     m_program->link();
//     m_posAttr = m_program->attributeLocation("posAttr");
//     m_colAttr = m_program->attributeLocation("colAttr");
//     m_matrixUniform = m_program->uniformLocation("matrix");
// }

    }
    void Update() override {
        qDebug() << "phase 2: Render Update";
        if (!isExposed())
            return;
        qDebug() << "phase 3";
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
        qDebug() <<"!!!!!!" << m_app;
        m_app->processEvents();

    }

     void Render() override {
        qDebug() << "phase 44";
        
        // Render
        const qreal retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);
        glClear(GL_COLOR_BUFFER_BIT);
        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            Engine::ObservingPointer<QTRenderComponent> r = static_cast<Engine::ObservingPointer<QTRenderComponent>>(ListRenderComponent[i]);

            r->CreateTexture();
        }
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

        glFlush();
        m_program->release();
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
};

#endif
