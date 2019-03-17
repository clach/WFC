#pragma once
#include "TileGrid.h"
#include <iostream>
#include <math.h>
#include "utils.h"

class WFC
{
public:
    WFC(GLWidget277 *context, std::string tileset, int x, int y, int z);
    ~WFC();

    TileGrid run();
    // TODO: add limit to number of iterations?

private:
    void setup();

    void clear();

    // return true if each cell has one remaining pattern
    bool observe();

    // return true if changes are still propagating
    bool propogate();

    // returns true if all cells at zero entropy (each cell has one remaining pattern)
    // returns false if not all cells at zero entropy, and returns cell
    // with lowest non-zero entropy
    // throws exception if contradiction (cell has no remaining patterns)
    bool findLowestEntropy(glm::vec3& cell, std::vector<int>& indices);

    TileGrid outputObservations() const;

    std::string jsonFilename;

    // desired dimensions of grid to fill with WFC
    glm::vec3 dim;

    bool periodic;

    double voxelSize;

    // number of total tile variant options
    int actionCount;

    std::vector<std::string> tileNames; // tile names
    std::vector<double> tileWeights; // tile weights (frequencies in input)
    std::vector<glm::mat4> tileRotations;

    std::vector<std::vector<std::vector<std::vector<bool>>>> wave;
    std::vector<std::vector<std::vector<bool>>> changes;
    std::vector<std::vector<std::vector<int>>> observed;
    std::vector<std::vector<std::vector<bool>>> propagator;

    GLWidget277 *context;

};
