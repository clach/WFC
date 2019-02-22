#pragma once
#include "tile.h"
#include <iostream>

class WFC
{
public:
    WFC(int x, int y, int z);
    ~WFC();

    void run();
    // TODO: add limit to number of iterations?

private:
    void extractPatterns();
    void buildPropogator();

    // return true if each cell has one remaining pattern
    bool observe();

    void propogate();

    // returns true if all cells at zero entropy (each cell has one remaining pattern)
    // returns false if not all cells at zero entropy, and returns cell
    // with lowest non-zero entropy
    // throws exception if contradiction (cell has no remaining patterns)
    bool findLowestEntropy(glm::vec3& cell, std::vector<int>& indices);

    glm::vec3 dim;
    std::vector<std::string> tiles;
    // TODO: some sort of data structure for relationships
    std::vector<std::vector<std::vector<std::vector<bool>>>> wave;

};
