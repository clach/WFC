#include "wfc.h"

WFC::WFC(int x, int y, int z) : dim(glm::vec3(x, y, z))
{
    // TODO:
    // instantiate tiles
    // instantiate rules

    // instantiate waves
    for (int i = 0; i < dim.x; i++) {
        std::vector<std::vector<std::vector<bool>>> waveY;
        for (int j = 0; j < dim.y; j++) {
            std::vector<std::vector<bool>> waveZ;
            for (int k = 0; k < dim.z; k++) {
                std::vector<bool> bools;
                for (int l = 0; l < tiles.size(); l++) {
                    bools.push_back(true);
                }
                waveZ.push_back(bools);
            }
            waveY.push_back(waveZ);
        }
        wave.push_back(waveY);
    }
}

void WFC::run()
{
    extractPatterns();
    buildPropogator();

    while (true) {
        bool cellsComplete = observe();
        if (cellsComplete) {
            break;
        }
        propogate();
    }

    // TODO: WFC is complete, output results
}

void WFC::extractPatterns() {
    // TODO
}

void WFC::buildPropogator(){
    // TODO
}


bool WFC::observe()
{
    glm::vec3 lowestEntropyCell;
    std::vector<int> remainingPatternIndices;
    try {
        if (findLowestEntropy(lowestEntropyCell, remainingPatternIndices)) {
            // each cell has one remaining pattern
            return true;
        } else {
            // of remaining patterns, choose one by random sample
            // TODO: weight by pattern frequency in source data
            int selectedPatternIndex = remainingPatternIndices[rand() % remainingPatternIndices.size()];

            std::vector<bool> bools = wave[lowestEntropyCell.x][lowestEntropyCell.y][lowestEntropyCell.z];

            // set bool array of cell to false, except for chosen pattern
            for (int i = 0; i < bools.size(); i++) {
                if (i == selectedPatternIndex) {
                    bools[i] = true;
                } else {
                    bools[i] = false;
                }
            }

            wave[lowestEntropyCell.x][lowestEntropyCell.y][lowestEntropyCell.z] = bools;
        }
    }
    catch (char* c) {
        std::cout << c << std::endl;
        exit(1);
    }

    return false;
}

void WFC::propogate()
{
    // TODO
}

// TODO: make sure this passing by reference works
bool WFC::findLowestEntropy(glm::vec3& cell, std::vector<int>& indices)
{
    // want to find lowest non-zero entropy
    // cell with one valid pattern has zero entropy
    // cell with no valid patterns is contradiction
    bool allCellsAtZeroEntropy = true;
    int min = INT_MAX;

    for (int i = 0; i < dim.x; i++) {
        for (int j = 0; j < dim.y; j++) {
            for (int k = 0; k < dim.z; k++) {

                std::vector<bool> bools = wave[i][j][k];
                int currEntropy = -1;
                std::vector<int> currIndices;
                for (int l = 0; l < bools.size(); l++) {
                    if (bools[l]) {
                        currEntropy++;
                        currIndices.push_back((l));
                    }
                }

                // if no valid patterns, throw exception
                // TODO: implement backtracking?
                if (currEntropy == -1) {
                    throw "No valid patterns";
                }

                if (currEntropy != 0) {
                    allCellsAtZeroEntropy = false;

                    if (currEntropy < min) {
                        min = currEntropy;
                        cell = glm::vec3(i, j, k);
                        indices = currIndices;
                    } else
                    {
                        // TODO: use some random noise to break ties
                    }
                }
            }
        }
    }

    return allCellsAtZeroEntropy;
}
