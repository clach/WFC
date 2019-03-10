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
    void setup(std::string jsonFilename);
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

    std::vector<std::string> tileNames;

    int pixelSize;
    int voxelSize;

    std::vector<std::vector<std::vector<std::vector<bool>>>> wave;
    std::vector<std::vector<std::vector<bool>>> changes;
    std::vector<std::vector<std::vector<int>>> observed;
    std::vector<float> stationary;
    std::vector<std::vector<std::vector<bool>>> propogator;

    int ground;
    bool perioidic;

    std::vector<float> logProg;
    float logT;


};
