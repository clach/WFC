#pragma once

#include <glwidget277.h>
#include <la.h>
#include <memory>

class Texture
{
public:
    Texture(GLWidget277* context);
    ~Texture();

    void create(const char *texturePath);
    void load(int texSlot);
    void bind(int texSlot);

private:
    GLWidget277* context;
    GLuint m_textureHandle;
    std::shared_ptr<QImage> m_textureImage;
};
