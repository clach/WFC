#include "tile.h"

Tile::Tile(GLWidget277 *context, TileGrid* tileGrid, std::string tileset) : Tile(context, tileGrid, tileset, "empty")
{}

Tile::Tile(GLWidget277 *context, TileGrid* tileGrid, std::string tileset, std::string name) :
    cardinality(0), objName(""), textureName(""), tileGrid(tileGrid), tileset(tileset), name(name),
    modelMat(glm::mat4()), context(context), mesh(context), visualizeEmptyTiles(false)
{
    setName(name);
}

Tile::Tile(const Tile &tile) : mesh(tile.context) {
    this->name = tile.name;
    this->objName = tile.objName;
    this->textureName = tile.textureName;
    this->modelMat = tile.modelMat;
    this->context = tile.context;
    this->tileset = tile.tileset;
    this->tileGrid = tile.tileGrid;
    this->cardinality = tile.cardinality;
    this->visualizeEmptyTiles = tile.visualizeEmptyTiles;
}

Tile& Tile::operator=(Tile& tile) {
    this->name = tile.name;
    this->objName = tile.objName;
    this->textureName = tile.textureName;
    this->modelMat = tile.modelMat;
    this->context = tile.context;
    this->tileset = tile.tileset;
    this->tileGrid = tile.tileGrid;
    this->cardinality = tile.cardinality;
    this->visualizeEmptyTiles = tile.visualizeEmptyTiles;
    return *this;
}


Tile::~Tile() {
    // TODO
}

void Tile::setName(std::string name) {
    this->name = name;
    if (name != "empty") {
        objName = ":/objs/" + tileset + "/" + name + ".obj";
        textureName = ":/objs/" + tileset + "/" + name + ".png";
    }
}

std::string Tile::getName() const {
    return name;
}

void Tile::setCardinality(int c) {
    this->cardinality = c;
}

int Tile::getCardinality() const {
    return cardinality;
}

void Tile::setTransform(glm::mat4 transform) {
    modelMat = transform;
}

void Tile::createTileMesh() {
    if (name != "empty") {
        const char* objNameChar = new char[objName.size()];
        const char* textureNameChar = new char[textureName.size()];
        objNameChar = &objName[0u];
        textureNameChar = &textureName[0u];

        mesh.createFromOBJ(objNameChar, textureNameChar);
        mesh.loadTexture();
    } else if (tileGrid->visualizeEmptyTiles()) {
        mesh.createCube();
    }
}

void Tile::drawTileMesh(ShaderProgram& sp){
    if (name != "empty" || tileGrid->visualizeEmptyTiles()) {
        sp.setModelMatrix(modelMat);
        sp.draw(mesh);
    }
}

void Tile::destroyTileMesh() {
    if (name != "empty" || tileGrid->visualizeEmptyTiles()) {
        mesh.destroy();
    }
}

void Tile::setVisualizeEmptyTiles(bool visualize) {
    this->visualizeEmptyTiles = visualize;
}


