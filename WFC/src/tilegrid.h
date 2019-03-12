#pragma once
#include <tile.h>

class TileGrid
{
public:
    TileGrid();
    TileGrid(int xDim, int yDim, int zDim);
    ~TileGrid();
    Tile& getTileAt(int x, int y, int z);
    void setTileAt(Tile& tile, int x, int y, int z);
    void createTiles();
    void drawTiles(ShaderProgram& sp);

private:
    glm::vec3 dim;
    std::vector<std::vector<std::vector<Tile>>> tiles;

};
