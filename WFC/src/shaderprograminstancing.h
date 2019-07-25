#pragma once
#include "shaderprogram.h"

class ShaderProgramInstancing : public ShaderProgram
{
public:
    ShaderProgramInstancing(GLWidget277* context);
    void create(const char *vertfile, const char *fragfile) override;
    void draw(Drawable &d) override;

    int attrTrans;
    int attrRot;

};

