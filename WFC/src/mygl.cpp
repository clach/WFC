#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include "wfc.h"


MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      m_geomCylinder(this), m_geomSphere(this),
      m_quad(this), someMesh(this),
      m_progLambert(this), m_progFlat(this), prog_skeleton(this),
      m_glCamera(), tileGrid()
{}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomCylinder.destroy();
    m_geomSphere.destroy();
    m_quad.destroy();
    someMesh.destroy();
    tileGrid.destroyTiles();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.53, 0.81, 0.92, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    //Create the instances of Cylinder and Sphere.
    m_geomCylinder.create();

    m_geomSphere.create();

    m_quad.create();

    createMeshes();

    // TODO: make these into input controls
    std::string tileset = "knots";
    WFC wfc = WFC(this, tileset, 5, 2, 5);
    tileGrid = wfc.run();
    tileGrid.createTiles();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    m_progLambert.setGeometryColor(glm::vec4(1.0, 0, 0, 1.0));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    //    vao.bind();
    glBindVertexArray(vao);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setModelMatrix(glm::mat4());

    m_progFlat.setModelMatrix(glm::translate(glm::mat4(), glm::vec3(0.0, -1.0, 0.0)));
    m_progFlat.draw(m_quad);

    //m_progLambert.setModelMatrix(glm::scale(glm::mat4(), glm::vec3(0.05)));
    //m_progLambert.draw(someMesh);

    tileGrid.drawTiles(m_progLambert);

}


void MyGL::keyPressEvent(QKeyEvent *e)
{

    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }

    switch (e->key()) {
    case Qt::Key_Escape:
        QApplication::quit();
        break;
    case Qt::Key_Right:
        m_glCamera.RotateAboutUp(-amount);
        break;
    case Qt::Key_Left:
        m_glCamera.RotateAboutUp(amount);
        break;
    case Qt::Key_Up:
        m_glCamera.RotateAboutRight(amount);
        break;
    case Qt::Key_Down:
        m_glCamera.RotateAboutRight(-amount);
        break;
    case Qt::Key_1:
        m_glCamera.fovy += amount;
        break;
    case Qt::Key_2:
        m_glCamera.fovy -= amount;
        break;
    case Qt::Key_W:
        m_glCamera.TranslateAlongLook(amount);
        break;
    case Qt::Key_S:
        m_glCamera.TranslateAlongLook(-amount);
        break;
    case Qt::Key_D:
        m_glCamera.TranslateAlongRight(amount);
        break;
    case Qt::Key_A:
        m_glCamera.TranslateAlongRight(-amount);
        break;
    case Qt::Key_Q:
        m_glCamera.TranslateAlongUp(-amount);
        break;
    case Qt::Key_E:
        m_glCamera.TranslateAlongUp(amount);
        break;
    case Qt::Key_R:
        m_glCamera = Camera(this->width(), this->height());
        break;
    }

    m_glCamera.RecomputeAttributes();
    update();  // Calls paintGL, among other things
}

// completely updates the scene related to the mesh
// repopulats list widgets in mainwindow
void MyGL::updateMeshScene() {
    update();
}

void MyGL::createMeshes() {
    //someMesh.createFromOBJ(":/objs/tower_top.obj", ":/objs/tower_top.png");
    someMesh.createFromOBJ(":/objs/wahoo.obj", ":/objs/wahoo.bmp");
    someMesh.loadTexture();
}
