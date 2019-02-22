#include "texture.h"
#include <QImage>

Texture::Texture(GLWidget277 *context)
    : context(context), m_textureHandle(-1), m_textureImage(nullptr)
{}

Texture::~Texture()
{}

void Texture::create(const char *texturePath)
{
    context->printGLErrorLog();

    QImage img(texturePath);
    img.convertToFormat(QImage::Format_ARGB32);
    img = img.mirrored();
    m_textureImage = std::make_shared<QImage>(img);
    context->glGenTextures(1, &m_textureHandle);

    context->printGLErrorLog();
}

void Texture::load(int texSlot = 0)
{
    context->printGLErrorLog();

    context->glActiveTexture(GL_TEXTURE0 + texSlot);
    context->glBindTexture(GL_TEXTURE_2D, m_textureHandle);

    // These parameters need to be set for EVERY texture you create
    // They don't always have to be set to the values given here, but they do need
    // to be set
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    context->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                          m_textureImage->width(), m_textureImage->height(),
                          0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, m_textureImage->bits());
    context->printGLErrorLog();
}


void Texture::bind(int texSlot = 0)
{
    context->glActiveTexture(GL_TEXTURE0 + texSlot);
    context->glBindTexture(GL_TEXTURE_2D, m_textureHandle);
}
