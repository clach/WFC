#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/quad.h>
#include "scene/camera.h"
#include "mainwindow.h"
#include <scene/mesh.h>
#include <tilegrid.h>
#include <wfc.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class MyGL
    : public GLWidget277
{
    Q_OBJECT

private:
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera m_glCamera;

    Quad groundQuad;
    glm::vec4 groundQuadColor;

    Quad selectionQuad;
    glm::vec4 selectionQuadColor;

    Mesh someMesh;

    bool buildMode;

    WFC wfc;
    TileGrid tileGrid;
    glm::vec3 dim;
    std::string tileset;

    bool checkToAddTile(glm::mat4 groundQuadTransMat, glm::vec3* posToDraw) const;

    void drawSelectionQuad(glm::vec3 pos);


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void createMeshes();

    void runWFC();

    void clearWFC();

    void setTileset(std::string tileset);

    void setBuildMode(bool buildMode);

    void setDimX(int x);
    void setDimY(int y);
    void setDimZ(int z);

protected:
    void keyPressEvent(QKeyEvent *e);

signals:

};


#endif // MYGL_H
