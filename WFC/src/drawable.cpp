#include "drawable.h"
#include <la.h>

Drawable::Drawable(GLWidget277* context)
    : bufIdx(), bufPos(), bufNor(), bufUV(), bufCol(), bufTrans(), bufRot(),
      idxBound(false), posBound(false), norBound(false), uvBound(false), colBound(false),
      transBound(false), rotBound(false), mp_context(context), numInstances(0)
{}


void Drawable::destroy()
{
    mp_context->glDeleteBuffers(1, &bufIdx);
    mp_context->glDeleteBuffers(1, &bufPos);
    mp_context->glDeleteBuffers(1, &bufNor);
    mp_context->glDeleteBuffers(1, &bufUV);
    mp_context->glDeleteBuffers(1, &bufCol);
    mp_context->glDeleteBuffers(1, &bufTrans);
    mp_context->glDeleteBuffers(1, &bufRot);
}

GLenum Drawable::drawMode()
{
    return GL_TRIANGLES;
}

int Drawable::elemCount()
{
    return count;
}

void Drawable::generateIdx()
{
    idxBound = true;
    mp_context->glGenBuffers(1, &bufIdx);
}

void Drawable::generatePos()
{
    posBound = true;
    mp_context->glGenBuffers(1, &bufPos);
}

void Drawable::generateNor()
{
    norBound = true;
    mp_context->glGenBuffers(1, &bufNor);
}

void Drawable::generateUV()
{
    uvBound = true;
    mp_context->glGenBuffers(1, &bufUV);
}

void Drawable::generateCol()
{
    colBound = true;
    mp_context->glGenBuffers(1, &bufCol);
}

void Drawable::generateTrans()
{
    transBound = true;
    mp_context->glGenBuffers(1, &bufTrans);
}

void Drawable::generateRot()
{
    rotBound = true;
    mp_context->glGenBuffers(1, &bufRot);
}

bool Drawable::bindIdx()
{
    if(idxBound) {
        mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    }
    return idxBound;
}

bool Drawable::bindPos()
{
    if(posBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    }
    return posBound;
}

bool Drawable::bindNor()
{
    if(norBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    }
    return norBound;
}

bool Drawable::bindUV()
{
    if(uvBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
    }
    return uvBound;
}

bool Drawable::bindCol()
{
    if(colBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    }
    return colBound;
}

bool Drawable::bindTrans()
{
    if(transBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufTrans);
    }
    return transBound;
}

bool Drawable::bindRot()
{
    if(rotBound){
        mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufRot);
    }
    return rotBound;
}

int Drawable::getNumInstances()
{
    return numInstances;
}

void Drawable::setNumInstances(int num)
{
    this->numInstances = num;
}
