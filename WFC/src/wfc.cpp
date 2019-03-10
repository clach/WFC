#include "wfc.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


WFC::WFC(int x, int y, int z) : dim(glm::vec3(x, y, z)), ground(-1)
{
    // TODO:
    // instantiate tiles
    // instantiate rules
    setup(":/json/knots.json");

    std::vector<int> tiles;

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

WFC::~WFC()
{
    // TODO
}

void WFC::setup(std::string jsonFilename) {
    // TODO: read json file
    QString jsonString;
    QFile jsonFile;
    jsonFile.setFileName(QString::fromStdString(jsonFilename));
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonString = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    QJsonArray tilesArray = jsonObject["tiles"].toArray();
    // if string convert to string (toString())
    // is arr convert to QJsonArray (toArray())

    int i = 5;

}

void WFC::run()
{

    extractPatterns();
    buildPropogator();

    while (true) {
        bool wfcComplete = observe();
        if (wfcComplete) { // returns true when WFC is complete
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
    /*
     *
    let neighbors = json.set.neighbors;
    for (var itr = 0; itr < neighbors.length; ++itr) {
      let neighbor = neighbors[itr];
      let type = neighbor[0] || "horizontal";
      let leftArr = neighbor[1].split(' ');
      let rightArr = neighbor[2].split(' ');

      if (leftArr.length == 1) {
        leftArr.push("0");
      }

      if (rightArr.length == 1) {
        rightArr.push("0");
      }

      let L = actions[firstOccurence[leftArr[0]]][Number.parseInt(leftArr[1])];
      let D = actions[L][1];

      let R = actions[firstOccurence[rightArr[0]]][Number.parseInt(rightArr[1])];
      let U = actions[R][1];

      if (type == "horizontal") {
        this.propagator[0][R][L] = true;
        this.propagator[0][actions[R][6]][actions[L][6]] = true;
        this.propagator[0][actions[L][4]][actions[R][4]] = true;
        this.propagator[0][actions[L][2]][actions[R][2]] = true;

        this.propagator[1][U][D] = true;
        this.propagator[1][actions[D][6]][actions[U][6]] = true;
        this.propagator[1][actions[U][4]][actions[D][4]] = true;
        this.propagator[1][actions[D][2]][actions[U][2]] = true;
      }
      else {
        for (let itr2 = 0; itr2 < 8; itr2++) {
          this.propagator[4][actions[L][itr2]][actions[R][itr2]] = true;
        }
      }
    }

    for (let t2 = 0; t2 < this.actionCount; t2++) {
      for (let t1 = 0; t1 < this.actionCount; t1++) {
        this.propagator[2][t2][t1] = this.propagator[0][t1][t2];
        this.propagator[3][t2][t1] = this.propagator[1][t1][t2];
        this.propagator[5][t2][t1] = this.propagator[4][t1][t2];
      }
    }*/
}


bool WFC::observe()
{
    glm::vec3 lowestEntropyCell;
    std::vector<int> remainingPatternIndices;
    try {
        if (findLowestEntropy(lowestEntropyCell, remainingPatternIndices)) {
            // each cell has one remaining pattern, WFC is complete
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
