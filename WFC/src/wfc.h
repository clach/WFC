#pragma once
#include <iostream>
#include <math.h>
#include "utils.h"
#include "tile.h"

//class Tile;
//class TileGrid;

class WFC
{
public:
    WFC(GLWidget277 *context);
    WFC(GLWidget277 *context, std::string tileset, int x, int y, int z);
    ~WFC();

    void setDim(int x, int y, int z);
    void setTileset(std::string tileset);
    void setPeriodic(bool periodic);
    void setSky(bool sky);
    void setBuildIndices(std::vector<glm::vec3> buildIndices);
    std::vector<glm::vec3> getBuildIndices() const;
    bool run(std::vector<std::vector<std::vector<Tile>>>* tiles);
    bool runIteration(std::vector<std::vector<std::vector<Tile>>>* tiles);


    float getVoxelSize() const;

    glm::mat4 calculateTileTransform(glm::vec3 pos, int cardinality) const;

    //TileGrid* tileGrid;

    int getMaxCardinality(std::string tileName);

private:
    void setup(std::vector<std::vector<std::vector<Tile>>>* tiles);

    void parseTileset();

    void clear();

    // return true if each cell has one remaining pattern
    bool observe();

    // return true if changes are still propagating
    bool propagate();

    // returns true if all cells at zero entropy (each cell has one remaining pattern)
    // returns false if not all cells at zero entropy, and returns cell
    // with lowest non-zero entropy
    // throws exception if contradiction (cell has no remaining patterns)
    bool findLowestEntropy(glm::vec3& cell, std::vector<int>& indices);

    void findObserved();

    bool outputObservations(std::vector<std::vector<std::vector<Tile>>>* tiles) const;

    bool tilesetChanged;

    bool inSubset(std::string tileName);

    int emptyIndex;
    int groundIndex;

    GLWidget277 *context;
    glm::vec3 dim; // desired dimensions of grid to fill with WFC
    std::string tileset; // name of WFC tileset

    bool periodic;
    bool sky;
    bool ground;
    float voxelSize; // size of input voxel obj
    int actionCount; // number of total tile variant options

    std::vector<std::string> subsetTileNames;

    std::vector<glm::vec3> buildIndices;

    std::map<std::string, int> firstOccurence;

    std::map<std::string, int> maxCardinalities;

    std::vector<std::string> tileNames; // tile names
    std::vector<double> tileWeights; // tile weights (frequencies in input)

    std::vector<std::vector<std::vector<std::vector<bool>>>> wave;
    std::vector<std::vector<std::vector<bool>>> changes;
    std::vector<std::vector<std::vector<int>>> observed;
    std::vector<std::vector<std::vector<bool>>> propagator;

};
