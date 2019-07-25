#pragma once

#include <glwidget277.h>
#include <la.h>

class Drawable
{
protected:
    int count;
    GLuint bufIdx;
    GLuint bufPos;
    GLuint bufNor;
    GLuint bufUV;
    GLuint bufCol;
    GLuint bufTrans;
    GLuint bufRot;

    bool idxBound;
    bool posBound;
    bool norBound;
    bool uvBound;
    bool colBound;
    bool transBound;
    bool rotBound;

    GLWidget277* mp_context; // Since Qt's OpenGL support is done through classes like QOpenGLFunctions_3_2_Core,
                          // we need to pass our OpenGL context to the Drawable in order to call GL functions
                          // from within this class.

    int numInstances;


public:
    Drawable(GLWidget277* context);

    virtual void create() = 0;
    void destroy(); // Frees the VBOs of the Drawable.

    virtual GLenum drawMode();
    int elemCount();

    void generateIdx();
    void generatePos();
    void generateNor();
    void generateUV();
    void generateCol();
    void generateTrans();
    void generateRot();

    bool bindIdx();
    bool bindPos();
    bool bindNor();
    bool bindUV();
    bool bindCol();
    bool bindTrans();
    bool bindRot();

    void setNumInstances(int num);
    int getNumInstances();

};
