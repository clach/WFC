#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>

MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent), buildMode(false),
      groundQuad(this), selectionQuad(this),
      groundQuadColor(glm::vec4(0.13, 0.55, 0.13, 0.6)), selectionQuadColor(glm::vec4(1.0, 1.0, 1.0, 0.5)),
      m_progLambert(this), m_progLambertInstancing(this), m_progLambertPrev(this), m_progFlat(this),
      m_glCamera(), lines(this), tileGrid(this), dim(glm::vec3(5, 2, 5)), tileset(""),
      selectedTile(EMPTY), groundQuadHeight(0), drawSelectionQuad(false),
      periodicPreview(false), tileGridRepeater(this, 3), tileDrawSize(3.f),
      iterTimer(0), iterativeWFC(false)
{
    setMouseTracking(true);

    // connect the timer to a function so that when the timer ticks the function is executed
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    // tell the timer to redraw 60 times per second
    timer.start(16);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    groundQuad.destroy();
    selectionQuad.destroy();
    lines.destroy();
    tileGrid.destroyTiles();
    tileGridRepeater.destroyTiles();
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
    groundQuad.setColor(groundQuadColor);
    groundQuad.create();
    selectionQuad.setColor(selectionQuadColor);
    selectionQuad.create();
    lines.create();

    // run initial wave function collapse
    runWFC();

    // create shaders
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    m_progLambertInstancing.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    m_progLambertPrev.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    m_progLambert.setGeometryColor(glm::vec4(1, 0, 0, 1));
    m_progLambertInstancing.setGeometryColor(glm::vec4(1, 0, 0, 1));
    m_progLambertPrev.setGeometryColor(glm::vec4(1, 0.4, 0.4, 1));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    // vao.bind();
    glBindVertexArray(vao);
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    m_progLambert.setViewProjMatrix(viewproj);
    m_progLambertInstancing.setViewProjMatrix(viewproj);
    m_progLambertPrev.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambertInstancing.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambertPrev.setViewProjMatrix(m_glCamera.getViewProj());
    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());


    // draw boundary lines
    glm::mat4 linesScale = glm::scale(glm::mat4(), glm::vec3(tileDrawSize * dim.x, tileDrawSize * dim.y, tileDrawSize * dim.z));
    m_progFlat.setModelMatrix(linesScale);
    m_progFlat.draw(lines);

    // draw tiles
    tileGrid.drawTiles(m_progLambertInstancing);

    // draw preview of periodic tilegrid tiling
    if (periodicPreview) {
        tileGridRepeater.drawTiles(m_progLambertPrev);
    }

    // draw ground quad
    glm::mat4 groundQuadScale = glm::scale(glm::mat4(), glm::vec3(tileDrawSize * dim.x, 1, tileDrawSize * dim.z));
    glm::mat4 groundQuadTrans = glm::translate(glm::mat4(), glm::vec3(0.0, tileDrawSize * groundQuadHeight, 0.0));
    groundQuadTransform = groundQuadTrans * groundQuadScale;
    m_progFlat.setModelMatrix(groundQuadTransform);
    m_progFlat.draw(groundQuad);

    // draw selection quad if desired
    if (drawSelectionQuad) {
        glm::mat4 selectionQuadScale = glm::scale(glm::mat4(), glm::vec3(tileDrawSize));
        glm::mat4 selectionQuadTrans = glm::translate(glm::mat4(), glm::vec3(selectionQuadPos.x * tileDrawSize,
                                                                             tileDrawSize * groundQuadHeight + 0.01,
                                                                             selectionQuadPos.z * tileDrawSize));
        glm::mat4 selectionQuadTransform = selectionQuadTrans * selectionQuadScale;
        m_progFlat.setModelMatrix(selectionQuadTransform);
        m_progFlat.draw(selectionQuad);
    }

}

void MyGL::timerUpdate() {
    //int time = 1000 / (dim.x * dim.y * dim.z); // TODO: be smart
    int time = 30;
    if (iterativeWFC && iterTimer % time == 0) {
        runWFCIteration();
    }
    iterTimer++;
    update();
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
    case Qt::Key_Minus:
        if (groundQuadHeight > 0) {
            groundQuadHeight--;
        }
        break;
    case Qt::Key_Equal:
        if (groundQuadHeight < dim.y - 1) {
            groundQuadHeight++;
        }
        break;
    }

    m_glCamera.RecomputeAttributes();
    update();
}

void MyGL::runWFC() {
    groundQuadHeight = 0;
    if (!buildMode) {
        tileGrid.destroyTiles();
        tileGrid.clear();
    }
    tileGrid.setDim(dim, buildMode, &buildIndices);

    if (!tileGrid.runWFC2()) {
        emit wfcConvergenceError(true);
        if (buildMode) {
            // if the WFC did not converge, clear the build indices
            // TODO: this is a little hacky, it's not necessarily the user's fault
            buildIndices.clear();
        }
    } else {
        emit wfcConvergenceError(false);
    }

    tileGrid.createTiles();

    if (periodicPreview) {
        tileGridRepeater.setTileGrid(tileGrid);
        tileGridRepeater.createTiles();
    }

    update();
}

void MyGL::startIterativeWFC() {
    groundQuadHeight = 0;
    if (!buildMode) {
        tileGrid.destroyTiles();
        tileGrid.clear();
    }
    tileGrid.setDim(dim, buildMode, &buildIndices);
    tileGrid.setupWFC();
    tileGrid.createTiles();

    iterativeWFC = true;
    emit wfcIterationInProgress(true);

    update();
}

void MyGL::runWFCIteration() {
    bool done = false;
    if (!tileGrid.runWFCIteration(done)) {
        emit wfcConvergenceError(true);
        if (buildMode) {
            // if the WFC did not converge, clear the build indices
            // TODO: this is a little hacky, it's not necessarily the user's fault
            buildIndices.clear();
        }
    } else {
        emit wfcConvergenceError(false);
    }

    if (done) {
        iterativeWFC = false;
        emit wfcIterationInProgress(false);
    }

    tileGrid.createTiles();

    if (periodicPreview) {
        tileGridRepeater.setTileGrid(tileGrid);
        tileGridRepeater.createTiles();
    }
}

void MyGL::clearTileGrid() {
    tileGrid.destroyTiles();
    tileGrid.clear();
    buildIndices.clear();
    tileGridRepeater.clear();
    tileGridRepeater.createTiles();
    update();
}

void MyGL::clearNonUserTiles() {
    tileGrid.clearNonUserTiles(buildIndices);
    update();
}

void MyGL::setBuildMode(bool buildMode) {
    this->buildMode = buildMode;
    clearTileGrid();
    if (!buildMode) {
        buildIndices.clear();
    }
}

void MyGL::setDimX(int x) {
    this->dim.x = x;
    tileGrid.setDim(dim, buildMode, &buildIndices);
    tileGrid.createTiles();
    tileGridRepeater.clear();
    tileGridRepeater.createTiles();
    update();
}

void MyGL::setDimY(int y) {
    this->dim.y = y;
    tileGrid.setDim(dim, buildMode, &buildIndices);
    tileGrid.createTiles();
    tileGridRepeater.clear();
    tileGridRepeater.createTiles();

    // ensure ground quad is never out of bounds of dim
    if (groundQuadHeight > dim.y - 1) {
        groundQuadHeight = dim.y - 1;
    }
    update();
}

void MyGL::setDimZ(int z) {
    this->dim.z = z;
    tileGrid.setDim(dim, buildMode, &buildIndices);
    tileGrid.createTiles();
    tileGridRepeater.clear();
    tileGridRepeater.createTiles();
    update();
}

void MyGL::setPeriodic(bool periodic) {
    tileGrid.setPeriodic(periodic);
}

void MyGL::setSky(bool sky) {
    tileGrid.setSky(sky);
}

void MyGL::showPeriodicPreview(bool preview) {
    periodicPreview = preview;
    if (preview) {
        tileGridRepeater.setTileGrid(tileGrid);
    } else {
        tileGridRepeater.clear();
    }
    tileGridRepeater.createTiles();
    update();
}

void MyGL::setTileset(std::string tileset) {
    if (this->tileset != tileset) {
        tileGrid.destroyTiles();
        tileGrid.clear();
        tileGridRepeater.destroyTiles();
        tileGrid.clear();
    }
    this->tileset = tileset;
    tileGrid.setTileset(tileset);
}

void MyGL::setSelectedTile(std::string tile) {
    this->selectedTile = tile;
}

glm::vec3 MyGL::convertWorldSpacePosToTileIndex(glm::vec3 pos) const {
    glm::vec3 tileIndex;
    tileIndex.x = (int)(pos.x / tileDrawSize);
    tileIndex.y = (int)(pos.y / tileDrawSize);
    tileIndex.z = (int)(pos.z / tileDrawSize);
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

void MyGL::mouseReleaseEvent(QMouseEvent *e) {
    if (buildMode) {
        if (e->button() == Qt::LeftButton) {
            // user left clicks to place tile
            glm::vec3 indices;
            if (getIntersectionWithGroundQuad(&indices)) {

                // check if location already has tile in it
                if (std::find(buildIndices.begin(), buildIndices.end(), indices) != buildIndices.end()) {
                    Tile tile = tileGrid.getTileAt(indices.x, indices.y, indices.z);
                    // if user is trying to place same tile that is already there
                    if (tile.getName() == selectedTile) {
                        // update rotation of tile
                        int cardinality = tile.getCardinality();
                        cardinality++;
                        int maxCardinality = tileGrid.getMaxCardinality(tile.getName());
                        if (maxCardinality != 0) {
                            cardinality %= maxCardinality;
                        }
                        tile.setCardinality(cardinality);
                        tile.setTransform(tileGrid.calculateTileTransform(indices, cardinality));

                        tileGrid.setTileAt(tile, indices.x, indices.y, indices.z);
                    } else {
                        // get tile to set
                        Tile tile = Tile(this, tileset);
                        tile.setName(selectedTile);
                        tile.setTransform(tileGrid.calculateTileTransform(indices, 0));

                        tileGrid.setTileAt(tile, indices.x, indices.y, indices.z);
                    }
                } else {
                    buildIndices.push_back(indices);

                    // get tile to set
                    Tile tile = Tile(this, tileset);
                    tile.setName(selectedTile);
                    tile.setTransform(tileGrid.calculateTileTransform(indices, 0));

                    tileGrid.setTileAt(tile, indices.x, indices.y, indices.z);
                }
                tileGrid.createTiles();
                update();
            }
        } else if (e->button() == Qt::RightButton) {
            // user right clicks to remove tile
            glm::vec3 indices;
            if (getIntersectionWithGroundQuad(&indices)) {
                if (std::find(buildIndices.begin(), buildIndices.end(), indices) != buildIndices.end()) {
                    // remove tile grid position from build indices
                    std::vector<glm::vec3>::iterator iter = std::find(buildIndices.begin(), buildIndices.end(), indices);
                    buildIndices.erase(iter);

                    // set empty tile in place
                    Tile tile = Tile(this, tileset);
                    tile.setTransform(tileGrid.calculateTileTransform(indices, 0));

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
        drawSelectionQuad = getIntersectionWithGroundQuad(&selectionQuadPos);
        update();
    }
}

