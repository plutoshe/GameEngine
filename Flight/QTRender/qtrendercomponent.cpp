#include "qtrendercomponent.h"

void QTRenderComponent::CreateSprite(std::string filename) {
    QImage tex, buf;
    buf.load(filename.c_str());
    gl_image=QGLWidget::convertToGLFormat(buf);
    //CreateTexture();
//    glGenTextures(1, &TextureID);
//    glBindTexture(GL_TEXTURE_2D, TextureID);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gl_image.width(), gl_image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, gl_image.bits());
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
