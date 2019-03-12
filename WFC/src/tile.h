#pragma once
#include "scene/mesh.h"
#include "shaderprogram.h"

class Tile
{
public:
    Tile();
    //Tile(char* objName, char* textureName);
    virtual ~Tile();
    void setName(std::string name);
    //void setTileMesh(char* objName, char* textureName);
    void createTileMesh();
    void drawTileMesh(ShaderProgram& sp);

    void setTransform(const glm::mat4 transform);

    void setRot(const glm::vec3 rot);
    void setTrans(const glm::vec3 trans);
    void setScale(const glm::vec3 scale);

private:
    char* objName;
    char* textureName;
    Mesh* mesh;

    // represent rotation, scale, etc somehow
    glm::mat4 transMat;
    glm::mat4 rotMat;
    glm::mat4 scaleMat;
    glm::mat4 modelMat;

};

