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
    void clearNonUserTiles(std::vector<glm::vec3> buildIndices);

    float getVoxelSize() const;
    std::string getTileset() const;

    void setTileset(std::string tileset);
    void setPeriodic(bool periodic);
    void setSky(bool sky);
    void setBuildMode(bool buildMode);

    void setupWFC();
    bool runWFC();
    bool runWFCIteration(bool& done);

    // want setDim to be able to modify buildIndices
    void setDim(glm::vec3 dim, bool keepTiles, std::vector<glm::vec3>* buildIndices);
    glm::vec3 getDim() const;

    glm::mat4 calculateTileTransform(glm::vec3 pos, int cardinality) const;
    int getMaxCardinality(std::string tileName) const;

private:
    GLWidget277 *context;
    WFC* wfc;
    glm::vec3 dim;
    std::string tileset;
    std::vector<std::vector<std::vector<Tile>>> tiles;
    bool buildMode;

    // TODO: info like this is shared between mygl, wfc, tilegrid, and tile
    // don't need to make members for each separate class?

};
