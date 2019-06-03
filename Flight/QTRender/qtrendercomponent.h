#ifndef QT_RENDER_COMPONENT
#define QT_RENDER_COMPONENT

#include "Engine/Engine.h"
#include <QOpenGLFunctions>
#include <QGLFramebufferObjectFormat>
#include <QImage>
#include <QOpenGLFunctions>
#include <QtDebug>

class QTRenderComponent : public RenderComponent, protected QOpenGLFunctions
{
public:
    QTRenderComponent() {}
    ~QTRenderComponent() {}
    bool needInitialize = true;
    GLuint TextureID;
    GLuint VBO, VboUV, IBO;
    GLuint posAttrLocation, texCoordAttrLocation;
    QImage gl_image;
    void CreateSprite(std::string filename);
    void Initialize() {
        initializeOpenGLFunctions();
    }
    void CreateVertexBuffer() {
        // Bind Vertex
        if (needInitialize) {
            Initialize();
            needInitialize = false;
        }
        qDebug() << "start";
        Vector3f vertices[4];
        vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
        vertices[1] = Vector3f(0.0f, 1.0f, 0.0f);
        vertices[2] = Vector3f(1.0f, 0.0f, 0.0f);
        vertices[3] = Vector3f(1.0f, 1.0f, 0.0f);
qDebug() << "start1";
        glGenBuffers(1, &VBO);
        qDebug() << "start2";
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
qDebug() << "finish vertex buffer";
        // Bind UV
        Vector2f uvs[4];
        uvs[0] = Vector2f(0.f, 0.f);
        uvs[1] = Vector2f(1.0f, 0.0f);
        uvs[2] = Vector2f(0.0f, 1.0f);
        uvs[3] = Vector2f(1.f, 1.f);

        glGenBuffers(1, &VboUV);
        glBindBuffer(GL_ARRAY_BUFFER, VboUV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
        qDebug() << "finish index buffer";
    }

    void CreateTexture() {
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gl_image.width(), gl_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, gl_image.bits());
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void CreateIndexBuffer() {
        unsigned int Indices[] = {
            0, 1, 2,
            1, 2, 3};

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    }

    void Render() override {
        qDebug() << "in component render";

        CreateVertexBuffer();
        CreateIndexBuffer();
        qDebug() << "posloc" << posAttrLocation;
        glClearColor(0.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(posAttrLocation);
        glEnableVertexAttribArray(texCoordAttrLocation);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(posAttrLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, VboUV);
        glVertexAttribPointer(texCoordAttrLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), nullptr);
qDebug() << "posloc" << posAttrLocation;
qDebug() << "texloc" << texCoordAttrLocation;
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        glDisableVertexAttribArray(posAttrLocation);
        glDisableVertexAttribArray(texCoordAttrLocation);



    }

};
#endif
