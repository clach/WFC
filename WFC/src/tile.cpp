#include "tile.h"

Tile::Tile() :
    objName(nullptr), textureName(nullptr), mesh(nullptr),
    transMat(glm::mat4()), rotMat(glm::mat4()), scaleMat(glm::mat4()),
    modelMat(glm::mat4())
{}

Tile::~Tile() {
    delete mesh;
}

void Tile::createTileMesh() {
    //this->objName = objName;
    //this->textureName = textureName;
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
