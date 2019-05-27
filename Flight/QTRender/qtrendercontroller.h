#ifndef QT_RENDER_CONTROLLER
#define QT_RENDER_CONTROLLER

#include <QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include "Engine/Engine.h"
#include "openglwindow.h"
#include <fstream>

class QTRenderController :  public OpenGLWindow, public RenderController
{
public:
    QOpenGLShaderProgram *m_program;

    QTRenderController() {}
    ~QTRenderController() {}
    const char* pVSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.vs";
    const char* pFSFileName = "D:/plutoshe/projects/qt/build-opengltest-Desktop_Qt_5_12_3_MSVC2017_64bit-Debug/debug/shader.fs";


    void Initialize()
    {
        m_program = new QOpenGLShaderProgram(this);
        std::string vertexShaderSource, fragmentShaderSource;
        file_reader(pVSFileName,  vertexShaderSource);
        file_reader(pFSFileName, fragmentShaderSource);
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str());
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str());
        m_program->link();
    }

    void Render()  {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
        glShadeModel(GL_SMOOTH);
        glLoadIdentity();

        for (size_t i = 0; i < ListRenderComponent.size(); i++) {
            ListRenderComponent[i]->Render();
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
