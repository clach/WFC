#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent), buildMode(false),
      groundQuad(this), selectionQuad(this),
      groundQuadColor(glm::vec4(0.0, 1.0, 0.0, 1.0)), selectionQuadColor(glm::vec4(1.0, 1.0, 1.0, 0.5)),
      m_progLambert(this), m_progFlat(this),
      m_glCamera(), someMesh(this), wfc(this), tileGrid(), dim(glm::vec3(5, 2, 5)), tileset("knots")
{}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    groundQuad.destroy();
    selectionQuad.destroy();
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

    // enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    // create geometry
    groundQuad.create();
    selectionQuad.create();
    createMeshes();

    runWFC();

    // create shaders
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
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

    float voxelSize = tileGrid.getVoxelSize();

    // draw ground quad
    glm::mat4 quadScale = glm::scale(glm::mat4(), glm::vec3(voxelSize * dim.x, 1, voxelSize * dim.z));
    glm::mat4 quadTrans = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 groundQuadTransform = quadTrans * quadScale;
    m_progFlat.setModelMatrix(groundQuadTransform);
    m_progFlat.setGeometryColor(groundQuadColor);
    m_progFlat.draw(groundQuad);

    // TODO
    // get raycast
    // draw selction quad
    glm::vec3 posToDraw;

    if (buildMode) {
        if (checkToAddTile(groundQuadTransform, &posToDraw)) {
            //posToDraw = glm::vec3(0, 0, 0);
            drawSelectionQuad(posToDraw);
        }
    }

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

void MyGL::createMeshes() {
    //someMesh.createFromOBJ(":/objs/tower_top.obj", ":/objs/tower_top.png");
    someMesh.createFromOBJ(":/objs/wahoo.obj", ":/objs/wahoo.bmp");
    someMesh.loadTexture();
}

void MyGL::runWFC() {
    tileGrid.destroyTiles();
    wfc.setDim(dim.x, dim.y, dim.z);
    wfc.setTileset(tileset);
    tileGrid = wfc.run();
    tileGrid.createTiles();
    update();
}

void MyGL::clearWFC() {
    // TODO: this leads to opengl invalid values
    tileGrid.destroyTiles();
    update();
}

void MyGL::setBuildMode(bool buildMode) {
    this->buildMode = buildMode;

    if (buildMode) {
        selectionQuad.create();
        tileGrid.destroyTiles();

    } else {
        selectionQuad.destroy();
    }

    update();
}

void MyGL::setDimX(int x) {
    this->dim.x = x;
    update();
}

void MyGL::setDimY(int y) {
    this->dim.y = y;
    update();
}

void MyGL::setDimZ(int z) {
    this->dim.z = z;
    update();
}

void MyGL::setTileset(std::string tileset) {
    this->tileset = tileset;
}

void MyGL::drawSelectionQuad(glm::vec3 pos) {
    float voxelSize = tileGrid.getVoxelSize();
    glm::mat4 quadScale = glm::scale(glm::mat4(), glm::vec3(voxelSize));
    glm::mat4 quadTrans = glm::translate(glm::mat4(), glm::vec3(pos.x * voxelSize, 0.01, pos.z * voxelSize));
    glm::mat4 quadTransform = quadTrans * quadScale;
    m_progFlat.setModelMatrix(quadTransform);
    m_progFlat.setGeometryColor(selectionQuadColor);
    m_progFlat.draw(selectionQuad);
}

bool MyGL::checkToAddTile(glm::mat4 groundQuadTransMat, glm::vec3* posToDraw) const {

    // ray march from camera
    glm::vec3 rayOrigin = m_glCamera.getEye();
    glm::vec3 rayDirection = m_glCamera.getLook();

    // start ray marching
    //float tFinal = 20.0; // final ray march distance
    //for (float t = 0; t <= tFinal; t += 0.01) {
       // glm::vec3 rayCurrent = rayOrigin + (t * rayDirection);

        // check intersection with ground quad
        // TODO: add more checks later
        glm::mat4 invTransMat = glm::inverse(groundQuadTransMat);

        glm::vec3 newOrigin = glm::vec3(invTransMat * glm::vec4(rayOrigin, 1.f));
        glm::vec3 newDirection = glm::vec3(invTransMat * glm::vec4(rayDirection, 0.f));

        // get intersection ground quad as plane
        glm::vec3 groundQuadNormal = glm::vec3(0, 1, 0);
        glm::vec3 groundQuadCenter = glm::vec3(0.5, 0.5, 0.5);
        float t = glm::dot(groundQuadNormal, groundQuadCenter - rayOrigin) /
                  glm::dot(groundQuadNormal, rayDirection);

        if (t < 0) {
            return false;
        }

        // now check if point of intersection falls in bounds of ground quad
        glm::vec3 pointOfIntersection = rayOrigin + t * rayDirection;

        if (pointOfIntersection.x >= 0 && pointOfIntersection.x <= 1 &&
            pointOfIntersection.z >= 0 && pointOfIntersection.z <= 1) {
            *posToDraw = pointOfIntersection;
            return true;
        }
    //}

    return false;
}


