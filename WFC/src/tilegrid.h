#pragma once
#include <tile.h>
#include <wfc.h>

class TileGrid
{
public:
    TileGrid();
    TileGrid(GLWidget277 *context);
    TileGrid(GLWidget277 *context, std::string tileset, int xDim, int yDim, int zDim);
    ~TileGrid();
    Tile getTileAt(int x, int y, int z) const;
    void setTileAt(Tile tile, int x, int y, int z);
    void createTiles();
    void drawTiles(ShaderProgram& sp);
    void destroyTiles();
    void clear(); // fills TileGrid with empty tiles

    float getVoxelSize() const;

    void setTileset(std::string tileset);

    void runWFC();

    void setDim(glm::vec3 dim, bool keepTiles, std::vector<glm::vec3> buildIndices);
    glm::vec3 getDim() const;

    glm::mat4 getTileTransform(glm::vec3 pos, glm::mat4 rotMat) const;

private:
    glm::vec3 dim;
    std::vector<std::vector<std::vector<Tile>>> tiles;

    // TODO: info like this is shared between mygl, wfc, tilegrid, and tile
    // don't need to make members for each separate class?
    GLWidget277 *context;
    std::string tileset;

    WFC wfc;


};
