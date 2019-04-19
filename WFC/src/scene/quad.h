#pragma once

#include "drawable.h"
#include <la.h>

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Quad : public Drawable
{
public:
    Quad(GLWidget277* mp_context);
    virtual void create();
    void setColor(glm::vec4 color);
private:
    glm::vec4 color;
};
