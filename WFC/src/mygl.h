#ifndef MYGL_H
#define MYGL_H

#include <QTimer>
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
#include <tilegridrepeater.h>
#include <wfc.h>


#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class MyGL : public GLWidget277
{
    Q_OBJECT

private:
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progLambertPrev;
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera m_glCamera;

    Quad groundQuad;
    glm::vec4 groundQuadColor;
    glm::mat4 groundQuadTransform;
    float groundQuadHeight;

    BoundaryLines lines;

    glm::vec3 selectionQuadPos;
    bool drawSelectionQuad;
    Quad selectionQuad;
    glm::vec4 selectionQuadColor;

    /// Timer linked to timerUpdate(). Fires approx. 60 times per second
    QTimer timer;

    int iterTimer;

    bool iterativeWFC;
    bool buildMode;
    bool periodicPreview;

    float tileDrawSize;

    TileGrid tileGrid;
    glm::vec3 dim;
    std::string tileset;
    std::string selectedTile;

    TileGridRepeater tileGridRepeater;

    std::vector<glm::vec3> buildIndices;

    bool checkToAddTile(glm::mat4 groundQuadTransMat, glm::vec3* posToDraw) const;
    glm::vec3 convertWorldSpacePosToTileIndex(glm::vec3 pos) const;
    bool getIntersectionWithGroundQuad(glm::vec3* posToDraw) const;

public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void runWFC();
    void startIterativeWFC();
    void runWFCIteration();

    void clearTileGrid();
    void clearNonUserTiles();

    void setTileset(std::string tileset);
    void setSelectedTile(std::string tile);
    void setBuildMode(bool buildMode);

    void setDimX(int x);
    void setDimY(int y);
    void setDimZ(int z);

    void setPeriodic(bool periodic);
    void setSky(bool sky);
    void showPeriodicPreview(bool preview);


protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:
    void wfcConvergenceError(bool);
    void wfcIterationInProgress(bool);

private slots:
    /// Slot that gets called ~60 times per second
    void timerUpdate();
};


#endif // MYGL_H
