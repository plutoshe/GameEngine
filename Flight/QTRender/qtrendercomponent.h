#ifndef QT_RENDER_COMPONENT
#define QT_RENDER_COMPONENT

#include "Engine/Engine.h"
#include <QOpenGLFunctions>
#include <QGLFramebufferObjectFormat>
#include <QImage>
#include <QOpenGLFunctions>

class QTRenderComponent : public RenderComponent, protected QOpenGLFunctions
{
public:
    QTRenderComponent() {}
    ~QTRenderComponent() {}

    GLuint TextureID;
    GLuint VBO, VboUV, IBO;

    void CreateSprite(std::string filename);

    void CreateVertexBuffer() {
        // Bind Vertex
        Vector3f vertices[4];
        vertices[0] = Vector3f(0.0f, 0.0f, 0.0f);
        vertices[1] = Vector3f(0.0f, 1.0f, 0.0f);
        vertices[2] = Vector3f(1.0f, 0.0f, 0.0f);
        vertices[3] = Vector3f(1.0f, 1.0f, 0.0f);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Bind UV
        Vector2f uvs[4];
        uvs[0] = Vector2f(0.f, 0.f);
        uvs[1] = Vector2f(1.0f, 0.0f);
        uvs[2] = Vector2f(0.0f, 1.0f);
        uvs[3] = Vector2f(1.f, 1.f);

        glGenBuffers(1, &VboUV);
        glBindBuffer(GL_ARRAY_BUFFER, VboUV);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    }

    void CreateIndexBuffer() {
        unsigned int Indices[] = {
            0, 1, 2,
            2, 3, 4};

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
    }

    void Render() {
        CreateVertexBuffer();
        CreateIndexBuffer();
        glClearColor(0.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, VboUV);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2f), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);


    }

};
#endif
