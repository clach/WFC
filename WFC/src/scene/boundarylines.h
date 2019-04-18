#pragma once
#include "drawable.h"

class BoundaryLines : public Drawable
{
public:
    BoundaryLines(GLWidget277 *context);
    virtual void create() override;
    virtual GLenum drawMode() override;
};

