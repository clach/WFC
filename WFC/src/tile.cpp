#include "tile.h"

Tile::Tile() :
    objName(nullptr), textureName(nullptr), mesh(nullptr),
    transMat(glm::mat4()), rotMat(glm::mat4()), scaleMat(glm::mat4()),
    modelMat(glm::mat4())
{}

Tile::~Tile() {
    // TODO
}

void Tile::setName(std::string name) {
    std::string objNameString = name + ".obj";
    objName = &objNameString[0u];
    std::string textureNameString = name + ".png";
    textureName = &textureNameString[0u];
}

void Tile::setTransform(glm::mat4 transform) {
    modelMat = transform;
}

void Tile::setTrans(glm::vec3 trans) {
    transMat = glm::translate(glm::mat4(), trans);
    modelMat = transMat * rotMat * scaleMat;
}

void Tile::setRot(glm::vec3 rot) {
    // do this later
    modelMat = transMat * rotMat * scaleMat;
}

void Tile::setScale(glm::vec3 scale) {
    scaleMat = glm::scale(glm::mat4(), scale);
    modelMat = transMat * rotMat * scaleMat;
}

void Tile::createTileMesh() {
    if (objName != nullptr) {
        mesh->createFromOBJ(objName, textureName);
        mesh->loadTexture();
    }
}

void Tile::drawTileMesh(ShaderProgram& sp){
    if (objName != nullptr) {
        sp.setModelMatrix(modelMat);
        sp.draw(*mesh);
    }
}
