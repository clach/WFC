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
    Cylinder m_geomCylinder;// The instance of a unit cylinder we can use to render any cylinder
    Sphere m_geomSphere;// The instance of a unit sphere we can use to render any sphere
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)
    ShaderProgram prog_skeleton; // shader program that transforms vertices based on skeleton joints

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera m_glCamera;

    Quad m_quad;

    Mesh someMesh;

    WFC wfc;
    TileGrid tileGrid;
    glm::vec3 dim;
    std::string tileset;

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void createMeshes();

    void runWFC();

    void setTileset(std::string tileset);

    void setDimX(int x);
    void setDimY(int y);
    void setDimZ(int z);

protected:
    void keyPressEvent(QKeyEvent *e);

signals:

};


#endif // MYGL_H
