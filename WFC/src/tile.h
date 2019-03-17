#pragma once
#include "scene/mesh.h"
#include "shaderprogram.h"

class Tile
{
public:
    Tile(GLWidget277 *context);

    Tile(const Tile &tile2); // copy constructor

    Tile& operator=(Tile& tile); // copy assignment operator

    //Tile(char* objName, char* textureName);
    virtual ~Tile();
    void setName(std::string name);
    //void setTileMesh(char* objName, char* textureName);
    void createTileMesh();
    void drawTileMesh(ShaderProgram& sp);
    void destroyTileMesh();
    void setTransform(const glm::mat4 transform);

private:
    GLWidget277 *context;

    std::string objName;
    std::string textureName;

    Mesh mesh;

    glm::mat4 modelMat;

};

