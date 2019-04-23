#pragma once
//#include <tile.h>
#include <tilegrid.h>

class TileGridRepeater
{
public:
    TileGridRepeater();
    TileGridRepeater(GLWidget277 *context, int numCopies);
    ~TileGridRepeater();

    void setTileGrid(const TileGrid& tileGrid);
    void createTiles();
    void drawTiles(ShaderProgram& sp);
    void destroyTiles();
    void clear();

private:
    GLWidget277 *context;
    glm::vec3 dim;
    std::vector<std::vector<std::vector<Tile>>> tiles;
    int numCopies;
    std::string tileset;

};
