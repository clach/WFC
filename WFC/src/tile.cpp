#include "tile.h"

Tile::Tile() : Tile(nullptr, "")
{}

Tile::Tile(GLWidget277 *context, std::string tileset) :
    Tile(context, tileset, EMPTY)
{}

Tile::Tile(GLWidget277 *context, std::string tileset, std::string name) :
    cardinality(0), objName(""), textureName(""), tileset(tileset), name(name),
    modelMat(glm::mat4()), context(context), mesh(context), bounds(context)
{
    setName(name);
}

Tile::Tile(const Tile &tile) : mesh(tile.context), bounds(tile.context) {
    this->name = tile.name;
    this->objName = tile.objName;
    this->textureName = tile.textureName;
    this->modelMat = tile.modelMat;
    this->context = tile.context;
    this->tileset = tile.tileset;
    this->cardinality = tile.cardinality;
}

Tile& Tile::operator=(Tile& tile) {
    this->name = tile.name;
    this->objName = tile.objName;
    this->textureName = tile.textureName;
    this->modelMat = tile.modelMat;
    this->context = tile.context;
    this->tileset = tile.tileset;
    this->cardinality = tile.cardinality;
    return *this;
}

Tile::~Tile() {
}

void Tile::setName(std::string name) {
    this->name = name;
    if (name != EMPTY && name != GROUND && name != BOUNDS) {
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
    if (name == BOUNDS) {
        bounds.create();
    } else if (name != EMPTY && name != GROUND) {
        const char* objNameChar = new char[objName.size()];
        const char* textureNameChar = new char[textureName.size()];
        objNameChar = &objName[0u];
        textureNameChar = &textureName[0u];

        mesh.createFromOBJ(objNameChar, textureNameChar);
        mesh.loadTexture();
    }
}

void Tile::drawTileMesh(ShaderProgram& sp){
    if (name == BOUNDS) {
        sp.setModelMatrix(modelMat);
        sp.draw(bounds);
    } else if (name != EMPTY && name != GROUND) {
        sp.setModelMatrix(modelMat);
        mesh.bindTexture();
        sp.draw(mesh);
    }
}

void Tile::destroyTileMesh() {
    if (name == BOUNDS) {
        bounds.destroy();
    } else if (name != EMPTY && name != GROUND) {
        mesh.destroy();
    }
}

