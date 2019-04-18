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
      m_glCamera(), someMesh(this), lines(this),
      tileGrid(this), dim(glm::vec3(5, 2, 5)), tileset("knots"),
      selectedTile("empty")
{
    setMouseTracking(true);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    groundQuad.destroy();
    selectionQuad.destroy();
    someMesh.destroy();
    lines.destroy();
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
    lines.create();
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
    groundQuadTransform = quadTrans * quadScale;
    m_progFlat.setModelMatrix(groundQuadTransform);
    m_progFlat.setGeometryColor(groundQuadColor);
    m_progFlat.draw(groundQuad);

    // draw bounary lines
    glm::mat4 linesScale = glm::scale(glm::mat4(), glm::vec3(voxelSize * dim.x, voxelSize * dim.y, voxelSize * dim.z));
    m_progFlat.setModelMatrix(linesScale);
    m_progFlat.draw(lines);

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
    if (!buildMode) {
        tileGrid.destroyTiles();
        tileGrid.clear();
    }
    tileGrid.setDim(dim, buildMode, buildIndices);
    tileGrid.setTileset(tileset);
    if (!tileGrid.runWFC() && buildMode) {
        // if the WFC did not converge, clear the build indices
        // TODO: this is a little hacky, it's not necessarily the user's fault
        buildIndices.clear();
    }
    tileGrid.createTiles();
    update();
}

void MyGL::clearTileGrid() {
    tileGrid.destroyTiles();
    tileGrid.clear();
    buildIndices.clear();
    update();
}

void MyGL::clearNonUserTiles() {
    // TODO
    for (int i = 0; i < buildIndices.size(); i++) {
    }
}


void MyGL::setBuildMode(bool buildMode) {
    this->buildMode = buildMode;
    if (buildMode) {
        clearTileGrid();
    } else {
        buildIndices.clear();
    }
}

void MyGL::setVisualizeEmptyTiles(bool visualize) {
    // TODO
    tileGrid.visualizeEmptyTiles(visualize);
    tileGrid.createTiles();
    update();
}

void MyGL::setDimX(int x) {
    this->dim.x = x;
    tileGrid.setDim(dim, buildMode, buildIndices);
    tileGrid.createTiles();
    update();
}

void MyGL::setDimY(int y) {
    this->dim.y = y;
    tileGrid.setDim(dim, buildMode, buildIndices);
    tileGrid.createTiles();
    update();
}

void MyGL::setDimZ(int z) {
    this->dim.z = z;
    tileGrid.setDim(dim, buildMode, buildIndices);
    tileGrid.createTiles();
    update();
}

void MyGL::setPeriodic(bool periodic) {
    tileGrid.setPeriodic(periodic);
}

void MyGL::setSky(bool sky) {
    tileGrid.setSky(sky);
}

void MyGL::setTileset(std::string tileset) {
    if (this->tileset != tileset) {
        tileGrid.destroyTiles();
        tileGrid.clear();
    }
    this->tileset = tileset;
}

void MyGL::setSelectedTile(std::string tile) {
    this->selectedTile = tile;
}

void MyGL::drawSelectionQuad(glm::vec3 pos) {
    float voxelSize = tileGrid.getVoxelSize();
    glm::mat4 quadScale = glm::scale(glm::mat4(), glm::vec3(voxelSize));
    glm::mat4 quadTrans = glm::translate(glm::mat4(), glm::vec3(pos.x * voxelSize, 0.01, pos.z * voxelSize));
    glm::mat4 quadTransform = quadTrans * quadScale;
    m_progFlat.setModelMatrix(quadTransform);
    m_progFlat.setGeometryColor(selectionQuadColor);
    // TODO: getting GL INVALID VALUES for this
    //m_progFlat.draw(selectionQuad);
    //update();
}

glm::vec3 MyGL::convertWorldSpacePosToTileIndex(glm::vec3 pos) const {
    glm::vec3 tileIndex;
    float voxelSize = tileGrid.getVoxelSize();
    tileIndex.x = (int)(pos.x / voxelSize);
    tileIndex.y = (int)(pos.y / voxelSize);
    tileIndex.z = (int)(pos.z / voxelSize);
    return tileIndex;
}

bool MyGL::getIntersectionWithGroundQuad(glm::vec3* posToDraw) const {
    QPoint p = this->mapFromGlobal(QCursor::pos());
    glm::vec2 point = glm::vec2(p.x(), p.y());
    Ray ray = m_glCamera.raycast(point);

    // transform ray into space of ground quad
    Ray transRay = ray.getTransformedCopy(glm::inverse(groundQuadTransform));
    glm::vec3 rayOrigin = transRay.origin;
    glm::vec3 rayDirection = transRay.direction;

    // get intersection with ground quad as plane
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
        // transform back to world space
        *posToDraw = glm::vec3(groundQuadTransform * glm::vec4(pointOfIntersection, 1));
        // transform to tile index
        *posToDraw = convertWorldSpacePosToTileIndex(*posToDraw);
        return true;
    }

    return false;
}


// TODO: there is some kind of bug, causes crashing
// try to place tiles at larger indices and run WFC
void MyGL::mouseReleaseEvent(QMouseEvent *e) {
    if (buildMode) {
        // user left clicks to place tile
        if (e->button() == Qt::LeftButton) {
            glm::vec3 indices;
            if (getIntersectionWithGroundQuad(&indices)) {

                buildIndices.push_back(indices);

                // get tile to set
                Tile tile = Tile(this, &tileGrid, tileset);
                tile.setName(selectedTile);

                // TODO: also control rotation somehow??
                glm::mat4 rotMat = glm::mat4();
                tile.setTransform(tileGrid.getTileTransform(indices, rotMat));

                tileGrid.setTileAt(tile, indices.x, indices.y, indices.z);
                tileGrid.createTiles();
                update();
            }

        // user right clicks to remove tile
        } else if (e->button() == Qt::RightButton) {

            glm::vec3 indices;
            if (getIntersectionWithGroundQuad(&indices)) {
                if (std::find(buildIndices.begin(), buildIndices.end(), indices) != buildIndices.end()) {

                    // remove tile grid position from build indices
                    std::vector<glm::vec3>::iterator iter = std::find(buildIndices.begin(), buildIndices.end(), indices);
                    int index = std::distance(buildIndices.begin(), iter);
                    buildIndices.erase(buildIndices.begin() + index);

                    // set empty tile in place
                    Tile tile = Tile(this, &tileGrid, tileset);
                    tile.setName("empty");

                    glm::mat4 rotMat = glm::mat4();
                    tile.setTransform(tileGrid.getTileTransform(indices, rotMat));

                    tileGrid.setTileAt(tile, indices.x, indices.y, indices.z);
                    tileGrid.createTiles();
                    update();
                }
            }
        }
    }
}

void MyGL::mouseMoveEvent(QMouseEvent *e) {
    glm::vec3 posToDraw;
    if (buildMode) {
        if (getIntersectionWithGroundQuad(&posToDraw)) {
            posToDraw = glm::vec3(0, 0, 0);
            drawSelectionQuad(posToDraw);
        }
    }
}



