#pragma once
#include <tile.h>

class TileGrid
{
public:
    TileGrid();
    TileGrid(GLWidget277 *context, std::string tileset, int voxelSize, int xDim, int yDim, int zDim);
    ~TileGrid();
    Tile getTileAt(int x, int y, int z) const;
    void setTileAt(Tile tile, int x, int y, int z);
    void createTiles();
    void drawTiles(ShaderProgram& sp);
    void destroyTiles();

    float getVoxelSize() const;
    glm::vec3 getDim() const;

private:
    glm::vec3 dim;
    std::vector<std::vector<std::vector<Tile>>> tiles;

    // TODO: info like this is shared between mygl, wfc, tilegrid, and tile
    // don't need to make members for each separate class?
    GLWidget277 *context;
    std::string tileset;
    float voxelSize;


};
