#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QGLFramebufferObjectFormat>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include "cyLib/cyTriMesh.h"
#include <QCoreApplication>
#include <QtDebug>
#include <QDir>>
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
    void loadVertex(cyTriMesh &trimesh, std::string filename) {
        qDebug(QString(filename.c_str()).toLatin1());
        trimesh.LoadFromFileObj(filename.c_str());
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

     void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
    {
        // 根据shader类型参数定义两个shader对象
        GLuint ShaderObj = glCreateShader(ShaderType);
        // 检查是否定义成功
        if (ShaderObj == 0) {
            fprintf(stderr, "Error creating shader type %d\n", ShaderType);
            exit(0);
        }
        qDebug(pShaderText);
        // 定义shader的代码源
        const GLchar* p[1];
        p[0] = pShaderText;
        GLint Lengths[1];
        Lengths[0]= strlen(pShaderText);
        glShaderSource(ShaderObj, 1, p, Lengths);
        glCompileShader(ShaderObj);// 编译shader对象

        // 检查和shader相关的错误
        GLint success;
        glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
            exit(1);
        }

        // 将编译好的shader对象绑定到program object程序对象上
        glAttachShader(ShaderProgram, ShaderObj);
    }

    // 编译着色器函数
    void CompileShaders()
    {
        // 创建着色器程序
        GLuint ShaderProgram = glCreateProgram();
        // 检查是否创建成功
        if (ShaderProgram == 0) {
            fprintf(stderr, "Error creating shader program\n");
            exit(1);
        }

        // 存储着色器文本的字符串缓冲
        std::string vs, fs;
        // 分别读取着色器文件中的文本到字符串缓冲区
        file_reader(QDir::currentPath().toStdString() + "/../opengltest/" + pVSFileName,  vs);
        file_reader(QDir::currentPath().toStdString() + "/../opengltest/" + pFSFileName, fs);
        qDebug(QString(vs.c_str()).toLatin1());
        // 添加顶点着色器和片段着色器
        AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
        AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

        // 链接shader着色器程序，并检查程序相关错误
        GLint Success = 0;
        GLchar ErrorLog[1024] = { 0 };
        glLinkProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
        if (Success == 0) {
            glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
            exit(1);
        }

        // 检查验证在当前的管线状态程序是否可以被执行
        glValidateProgram(ShaderProgram);
        glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
        if (!Success) {
            glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
            exit(1);
        }

        // 设置到管线声明中来使用上面成功建立的shader程序
        glUseProgram(ShaderProgram);
    }
public slots:
    //void UpdateAnimation();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;
    GLuint VBO;
    float rotation;
    cyTriMesh meshData;
    const char* pVSFileName = "shader.vs";
    const char* pFSFileName = "shader.fs";
};

#endif // MAINWINDOW_H
