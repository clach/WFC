#pragma once
#include "scene/mesh.h"
#include "shaderprogram.h"

class Tile
{
public:
    Tile(GLWidget277 *context, std::string tileset);
    Tile(GLWidget277 *context, std::string tileset, std::string name);
    Tile(const Tile &tile2); // copy constructor

    virtual ~Tile();

    Tile& operator=(Tile& tile); // copy assignment operator

    void setName(std::string name);
    std::string getName() const;
    void createTileMesh();
    void drawTileMesh(ShaderProgram& sp);
    void destroyTileMesh();
    void setTransform(const glm::mat4 transform);

private:
    GLWidget277 *context;

    std::string tileset;
    std::string name;
    std::string objName;
    std::string textureName;

    Mesh mesh;

    glm::mat4 modelMat;

};

