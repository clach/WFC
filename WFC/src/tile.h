#pragma once
#include "scene/mesh.h"
#include "scene/boundarylines.h"
#include "shaderprogram.h"

const std::string EMPTY = "empty";
const std::string GROUND = "ground";
const std::string BOUNDS = "bounds";

class Tile
{
public:
    Tile();
    Tile(GLWidget277 *context, std::string tileset);
    Tile(GLWidget277 *context, std::string tileset, std::string name);
    Tile(const Tile &tile); // copy constructor

    virtual ~Tile();

    Tile& operator=(Tile& tile); // copy assignment operator

    void setName(std::string name);
    std::string getName() const;

    void setCardinality(int c);
    int getCardinality() const;

    void createTileMesh();
    void drawTileMesh(ShaderProgram& sp);
    void destroyTileMesh();
    void setTransform(const glm::mat4 transform);

private:
    GLWidget277 *context;

    std::string tileset;
    std::string name;
    int cardinality;
    std::string objName;
    std::string textureName;

    Mesh mesh;
    BoundaryLines bounds;
    glm::mat4 modelMat;

};

