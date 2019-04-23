#pragma once
#include "scene/mesh.h"
#include "shaderprogram.h"
//#include "tilegrid.h"

//class TileGrid;

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
    //void setVisualizeEmptyTiles(bool visualize);

private:
    GLWidget277 *context;

    //TileGrid* tileGrid;

    std::string tileset;
    std::string name;
    int cardinality;
    std::string objName;
    std::string textureName;

    Mesh mesh;
    //bool visualizeEmptyTiles;

    glm::mat4 modelMat;

};

