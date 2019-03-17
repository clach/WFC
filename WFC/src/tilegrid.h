#pragma once
#include <tile.h>

class TileGrid
{
public:
    TileGrid();
    TileGrid(GLWidget277 *context, int xDim, int yDim, int zDim);
    ~TileGrid();
    Tile& getTileAt(int x, int y, int z);
    void setTileAt(Tile tile, int x, int y, int z);
    void createTiles();
    void drawTiles(ShaderProgram& sp);
    void destroyTiles();

private:
    glm::vec3 dim;
    std::vector<std::vector<std::vector<Tile>>> tiles;

    GLWidget277 *context;

};
