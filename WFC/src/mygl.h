#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/quad.h>
#include <scene/boundarylines.h>
#include <scene/camera.h>
#include <mainwindow.h>
#include <scene/mesh.h>
#include <tilegrid.h>
#include <wfc.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class MyGL : public GLWidget277
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
    glm::mat4 groundQuadTransform;
    float groundQuadHeight;

    glm::vec3 selectionQuadPos;
    bool drawSelectionQuad;
    Quad selectionQuad;
    glm::vec4 selectionQuadColor;

    Mesh someMesh;

    BoundaryLines lines;

    bool buildMode;

    TileGrid tileGrid;
    glm::vec3 dim;
    std::string tileset;
    std::string selectedTile;

    std::vector<glm::vec3> buildIndices;

    bool checkToAddTile(glm::mat4 groundQuadTransMat, glm::vec3* posToDraw) const;
    glm::vec3 convertWorldSpacePosToTileIndex(glm::vec3 pos) const;
    bool getIntersectionWithGroundQuad(glm::vec3* posToDraw) const;
    //void drawSelectionQuad(glm::vec3 pos);


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void createMeshes();

    void runWFC();

    void clearTileGrid();

    void clearNonUserTiles();

    void setTileset(std::string tileset);

    void setSelectedTile(std::string tile);

    void setBuildMode(bool buildMode);
    void setVisualizeEmptyTiles(bool visualize);

    void setDimX(int x);
    void setDimY(int y);
    void setDimZ(int z);

    void setPeriodic(bool periodic);
    void setSky(bool sky);

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void wfcConvergenceError(bool);
};


#endif // MYGL_H
