#include "tile.h"

Tile::Tile(GLWidget277 *context, std::string tileset) :
    objName(""), textureName(""), tileset(tileset), name("empty"),
    modelMat(glm::mat4()), context(context), mesh(context)
{
}

Tile::Tile(GLWidget277 *context, std::string tileset, std::string name) :
    objName(""), textureName(""), tileset(tileset), name(name),
    modelMat(glm::mat4()), context(context), mesh(context)
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
}

Tile& Tile::operator=(Tile& tile) {
    this->name = tile.name;
    this->objName = tile.objName;
    this->textureName = tile.textureName;
    this->modelMat = tile.modelMat;
    this->context = tile.context;
    this->tileset = tile.tileset;
    return *this;
}


Tile::~Tile() {
    // TODO
}

std::string Tile::getName() const {
    return name;
}


void Tile::setName(std::string name) {
    this->name = name;
    if (name != "empty") {
        objName = ":/objs/" + tileset + "/" + name + ".obj";
        textureName = ":/objs/" + tileset + "/" + name + ".png";
    }
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
    }
}

void Tile::drawTileMesh(ShaderProgram& sp){
    if (name != "empty") {
        sp.setModelMatrix(modelMat);
        sp.draw(mesh);
    }
}

void Tile::destroyTileMesh() {
    if (name != "empty") {
        mesh.destroy();
    }
}

