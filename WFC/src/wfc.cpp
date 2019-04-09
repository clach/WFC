#include "wfc.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <string.h>

// some general rules for index notation
// x, y, z used for positions in grid
// c used for cardinality
// t/t1/t2 used for action count
// d used for direction
// i, j, k used for everything else

WFC::WFC(GLWidget277 *context) : context(context),
    dim(glm::vec3()), periodic(false), sky(true), ground(false), voxelSize(1), actionCount(0),
    tileset(""), tilesetChanged(true), emptyIndex(-1)
{
}

WFC::WFC(GLWidget277 *context, std::string tileset, int x, int y, int z) :
    context(context), dim(glm::vec3(x, y, z)), periodic(false), sky(true), ground(false),
    voxelSize(1), actionCount(0), tileset(tileset), tilesetChanged(true), emptyIndex(-1)
{
}

WFC::~WFC()
{
}

void WFC::run(std::vector<std::vector<std::vector<Tile>>>* tiles)
{
    setup(tiles);

    while (true) {
        if (observe()) { // returns true when WFC is complete
            break;
        }
        // keep propogating until no more changes occur
        while (propogate()) {}
    }

    // WFC is complete, output results
    outputObservations(tiles);
}

bool WFC::inSubset(std::string tileName) {
    return std::find(subsetTileNames.begin(), subsetTileNames.end(), tileName) != subsetTileNames.end();
}

void WFC::parseTileset() {
    // parse json file
    QString jsonString;
    QFile jsonFile;
    std::string jsonFilename = ":/json/" + tileset + ".json";
    jsonFile.setFileName(QString::fromStdString(jsonFilename));
    jsonFile.open(QIODevice::ReadOnly | QIODevice::Text);
    jsonString = jsonFile.readAll();
    jsonFile.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();

    QJsonObject jsonTilesetObject = jsonObject["tileset"].toObject();
    voxelSize = jsonTilesetObject["voxelSize"].toDouble();
    periodic = jsonTilesetObject["periodic"].toBool();
    sky = jsonTilesetObject["sky"].toBool();
    ground = jsonTilesetObject["ground"].toBool();

    QJsonArray tilesArray = jsonTilesetObject["tiles"].toArray();
    QJsonArray neighborsArray = jsonTilesetObject["neighbors"].toArray();

    // TODO: implement subsets /////////////////////////////////////////////////////
    QJsonObject jsonSubsetsObject = jsonTilesetObject["subsets"].toObject();
    QJsonArray subsetTileNamesArray = jsonSubsetsObject["onlyTurns"].toArray();
    for (int i = 0; i < subsetTileNamesArray.size(); i++) {
        subsetTileNames.push_back(subsetTileNamesArray[i].toString().toStdString());
    }

    std::vector<std::vector<int>> action;
    firstOccurence = std::map<std::string, int>();

    for (int i = 0; i < tilesArray.size(); i++) {
        QJsonObject jsonTile = tilesArray[i].toObject();
        std::string tileName = jsonTile["name"].toString().toStdString();

        if (!inSubset(tileName)) {
            //continue;
        }
        char tileSym = jsonTile["symmetry"].toString("X").toStdString().at(0);
        double tileWeight = jsonTile["weight"].toDouble(1.0);

        // create two fxn pointers that map equivalent operations?
        // a is for rotation, b is for mirroring
        int (*a)(int);
        int (*b)(int);

        // cardinality is number of meaningful variants created from rotation and mirroring
        // here cardinality is at most 4, so variants can be 0, 1, 2, 3
        int cardinality;

        // (look at symmetry only in plane of view, like looking at 2D tile)
        switch (tileSym) {
        case 'L': {
            cardinality = 4;
            a = [](int c) { return (c + 1) % 4; };
            b = [](int c) { return c % 2 == 0 ? c + 1 : c - 1; };
            break;
        }
        case 'T': {
            cardinality = 4;
            a = [](int c) { return (c + 1) % 4; };
            b = [](int c) { return c % 2 == 0 ? c : 4 - c; };
            break;
        }
        case 'I': {
            cardinality = 2;
            a = [](int c) { return 1 - c; };
            b = [](int c) { return c; };
            break;
        }
        case '\\': {
            cardinality = 2;
            a = [](int c) { return 1 - c; };
            b = [](int c) { return 1 - c; };
            break;
        }
        default: { // case 'X': {
            cardinality = 1;
            a = [](int c) { return c; };
            b = [](int c) { return c; };
            break;
        }
        }

        actionCount = action.size();

        // keep track of first occurence of a tile within action
        firstOccurence[tileName] = actionCount;

        if (tileName == "empty") {
            emptyIndex = actionCount;
        }

        // handle mirrored and rotated tiles
        // (think symmetry of a square)
        // (there are only cardinality # of meaningful variants for a tile
        // m keeps track of how the operations produce those cardinality variants)
        for (int c = 0; c < cardinality; c++) {
            std::vector<int> m;

            // 4 possible rotations (0, 90, 180, and 270 deg)
            m.push_back(c);
            m.push_back(a(c));
            m.push_back(a(a(c)));
            m.push_back(a(a(a(c))));

            // 4 possible mirrors (|, \, -, /)
            m.push_back(b(c));
            m.push_back(b(a(c)));
            m.push_back(b(a(a(c))));
            m.push_back(b(a(a(a(c)))));

            // add offsets
            for (int j = 0; j < 8; j++) {
                m[j] += actionCount;
            }

            action.push_back(m); // push list of rotations and mirrors for tile
        }

        // push back tile names (with their variant number), tile weights, tile transforms
        // (all possible tile variants can be made with just rotation)
        for (int c = 0; c < cardinality; c++)
        {
            tileNames.push_back(tileName + " " + std::to_string(c));
            tileWeights.push_back(tileWeight);
            tileRotations.push_back(glm::eulerAngleY(c * PI / 2.0f));
        }
    }

    // re-update actionCount after all tiles and variants are added
    actionCount = action.size();

    // build propagator structure
    // create propagator starting data structure
    // 6 x actionCount x actionCount
    for (int d = 0; d < 6; d++) { // d is all possible directions
        std::vector<std::vector<bool>> propagatorY;
        for (int t2 = 0; t2 < actionCount; t2++) {
            std::vector<bool> propagatorZ;
            for (int t1 = 0; t1 < actionCount; t1++) {
                // set all neighbor relationships to false at start
                propagatorZ.push_back(false);
            }
            propagatorY.push_back(propagatorZ);
        }
        propagator.push_back(propagatorY);
    }

    // fill propogator based on neighbors array
    for (int i = 0; i < neighborsArray.size(); i++) {
        QJsonArray jsonNeighbor = neighborsArray[i].toArray();
        std::string neighborType = jsonNeighbor[0].toString().toStdString();

        std::string left = jsonNeighbor[1].toString().toStdString();
        std::string right = jsonNeighbor[2].toString().toStdString();
        std::string delimiter = " ";
        std::string leftName;
        std::string rightName;
        int leftNum;
        int rightNum;

        if (left.find(delimiter) != std::string::npos) {
            leftName = left.substr(0, left.find(delimiter));
            leftNum = std::stoi(left.substr(left.find(delimiter) + 1, left.length()));
        } else {
            leftName = left;
            leftNum = 0;
        }
        if (right.find(delimiter) != std::string::npos) {
            rightName = right.substr(0, right.find(delimiter));
            rightNum = std::stoi(right.substr(right.find(delimiter) + 1, right.length()));
        } else {
            rightName = right;
            rightNum = 0;
        }

        // check if current neighbor relationship involves tiles that belong to subset
        if (!inSubset(leftName) || !inSubset(rightName)) {
            //continue;
        }

        // TODO: understand this
        int L = action[firstOccurence[leftName]][leftNum];
        int D = action[L][1];
        int R = action[firstOccurence[rightName]][rightNum];
        int U = action[R][1];

        // propagator directions go -x, +y, +x, -y, +z, -z
        // TODO: maybe change that to be more intuitive?
        if (neighborType == "horizontal") { // x and z directions
            // -x direction
            propagator[0][R][L] = true;
            propagator[0][action[R][6]][action[L][6]] = true;
            propagator[0][action[L][4]][action[R][4]] = true;
            propagator[0][action[L][2]][action[R][2]] = true;

            // +z direction
            propagator[4][U][D] = true;
            propagator[4][action[D][6]][action[U][6]] = true;
            propagator[4][action[U][4]][action[D][4]] = true;
            propagator[4][action[D][2]][action[U][2]] = true;
        }
        else if (neighborType == "vertical") { // direction
            for (int j = 0; j < 8; j++) {
                // -y direction
                propagator[3][action[L][j]][action[R][j]] = true;
            }
        }
    }

    // copy over mirrored relationships for +x, +y, -z directions
    // (ex: if I can put t1 to the left of t2, I can put t2 to the right of t1)
    for (int t2 = 0; t2 < actionCount; t2++) {
        for (int t1 = 0; t1 < actionCount; t1++) {
            propagator[2][t2][t1] = propagator[0][t1][t2];
            propagator[1][t2][t1] = propagator[3][t1][t2];
            propagator[5][t2][t1] = propagator[4][t1][t2];
        }
    }
}

void WFC::setup(std::vector<std::vector<std::vector<Tile>>>* tiles) {
    // clear everything
    clear();

    if (tilesetChanged) {
        parseTileset();
    }

    //sky= false;

    if (sky && !ground) {
        dim += 2;
    }

    // instantiate wave, changes, observed structures
    // for each cell in grid, value of wave is vector of trues
    // value of changes is false
    // value of observed is -1
    for (int x = 0; x < dim.x; x++) {
        std::vector<std::vector<std::vector<bool>>> waveY;
        std::vector<std::vector<bool>> changesY;
        std::vector<std::vector<int>> observedY;

        for (int y = 0; y < dim.y; y++) {
            std::vector<std::vector<bool>> waveZ;
            std::vector<bool> changesZ;
            std::vector<int> observedZ;

            for (int z = 0; z < dim.z; z++) {
                std::vector<bool> bools;
                for (int t = 0; t < actionCount; t++) {
                    bools.push_back(true);
                }
                waveZ.push_back(bools);
                changesZ.push_back(false);
                observedZ.push_back(-1);
            }

            waveY.push_back(waveZ);
            changesY.push_back(changesZ);
            observedY.push_back(observedZ);
        }
        wave.push_back(waveY);
        changes.push_back(changesY);
        observed.push_back(observedY);
    }

    // add empty tiles on boundaries
    if (sky) {
        for (int x = 0; x < dim.x; x++) {
            for (int y = 0; y < dim.y; y++) {
                for (int z = 0; z < dim.z; z++) {
                    // if on a boundary
                    if (x == 0 || x == dim.x - 1 || y == 0 || y == dim.y - 1 || z == 0 || z == dim.z - 1) {
                        for (int t = 0; t < actionCount; t++) {
                            wave[x][y][z][t] = t == emptyIndex;
                        }
                        changes[x][y][z] = true;
                    }
                }
            }
        }

        propogate();
    }

    // fill with tiles passed from user
    int indexOffset = 0;

    if (sky) {
        indexOffset = 1;
    }

    for (int i = 0; i < buildIndices.size(); i++) {
        int x = buildIndices[i].x;
        int y = buildIndices[i].y;
        int z = buildIndices[i].z;

        Tile tile = (*tiles)[x][y][z];
        std::string name = tile.getName();

        int tileIndex = firstOccurence[name];
        // TODO: account for rotation of input tile!!
        std::vector<bool> bools = wave[x + indexOffset][y + indexOffset][z + indexOffset];

        // set bool array of selected cell to false, except for chosen tile
        for (int t = 0; t < actionCount; t++) {
            bools[t] = t == tileIndex;
        }

        wave[x + indexOffset][y + indexOffset][z + indexOffset] = bools;
        changes[x + indexOffset][x + indexOffset][z + indexOffset] = true;
    }

    // TODO: algorithm assumes all user input is valid
    propogate();

}

void WFC::clear() {
    if (tilesetChanged) {
        actionCount = 0;
        firstOccurence.clear();
        tileNames.clear();
        tileWeights.clear();
        tileRotations.clear();
        propagator.clear();
    }
    wave.clear();
    changes.clear();
    observed.clear();
}

bool WFC::observe()
{
    glm::vec3 cell;
    std::vector<int> remainingTileIndices;
    try {
        if (findLowestEntropy(cell, remainingTileIndices)) {
            // each cell has one remaining pattern, WFC is complete!
            return true;
        } else {
            // of remaining patterns, choose one by random sample
            // TODO: weight by tile frequency in source data
            int selectedTileIndex = remainingTileIndices[rand() % remainingTileIndices.size()];

            std::vector<bool> bools = wave[cell.x][cell.y][cell.z];
            // set bool array of selected cell to false, except for chosen tile
            for (int t = 0; t < actionCount; t++) {
                bools[t] = t == selectedTileIndex;
            }

            wave[cell.x][cell.y][cell.z] = bools;
            changes[cell.x][cell.y][cell.z] = true;
        }
    } catch (...) {
        std::cout << "No valid pattern found!" << std::endl;
        return true;
    }

    return false;
}

bool WFC::propogate()
{
    bool change = false; // did a change occur?

    for (int x2 = 0; x2 < dim.x; x2++) {
        for (int y2 = 0; y2 < dim.y; y2++) {
            for (int z2 = 0; z2 < dim.z; z2++) {
                for (int d = 0; d < 6; d++) {

                    // we are checking to see if there are changes in cell 2 given
                    // the bool values in cell 1
                    // (cell 1 is adjacent cell in some direction based on d)
                    // again, direction order: -x, +y, +x, -y, +z, -z
                    int x1 = x2;
                    int y1 = y2;
                    int z1 = z2;

                    // account for periodicity
                    switch (d) {
                    case 0: {
                        if (x2 == 0) {
                            if (!periodic) {
                                continue;
                            } else {
                                x1 = dim.x - 1;
                            }
                        } else {
                            x1 = x2 - 1;
                        }
                        break;
                    }
                    case 1:  {
                        if (y2 == dim.y - 1) {
                            if (!periodic) {
                                continue;
                            } else {
                                y1 = 0;
                            }
                        } else {
                            y1 = y2 + 1;
                        }
                        break;
                    }
                    case 2: {
                        if (x2 == dim.x - 1) {
                            if (!periodic) {
                                continue;
                            } else {
                                x1 = 0;
                            }
                        } else {
                            x1 = x2 + 1;
                        }
                        break;
                    }
                    case 3: {
                        if (y2 == 0) {
                            if (!periodic) {
                                continue;
                            }
                            else {
                                y1 = dim.y - 1;
                            }
                        } else {
                            y1 = y2 - 1;
                        }
                        break;
                    }
                    case 4: {
                        if (z2 == dim.z - 1) {
                            if (!periodic) {
                                continue;
                            } else {
                                z1 = 0;
                            }
                        } else {
                            z1 = z2 + 1;
                        }
                        break;
                    }
                    default: {
                        if (z2 == 0)
                        {
                            if (!periodic) {
                                continue;
                            }
                            else {
                                z1 = dim.z - 1;
                            }
                        } else {
                            z1 = z2 - 1;
                        }
                        break;
                    }
                    }

                    // if there are no changes to current cell, skip to next cell direction
                    if (!changes[x1][y1][z1]) {
                        continue;
                    }

                    std::vector<bool> bools1 = wave[x1][y1][z1];
                    std::vector<bool> bools2 = wave[x2][y2][z2];

                    // go through each action-action pair
                    for (int t2 = 0; t2 < actionCount; t2++) {

                        // if tile t2 is still possible in cell ijk
                        if (bools2[t2]) {
                            // but, t2 might not be possible if the bool values in adjacent cell xyz recently changed!

                            // get propagator for tile t2
                            std::vector<bool> prop = propagator[d][t2];
                            bool foundValidNeighbor = false;

                            // check if there are any valid tiles left for cell 1 if tile t2 goes into cell 2
                            for (int t1 = 0; t1 < actionCount && !foundValidNeighbor; t1++) {
                                // if tile t1 is possible in adjacent cell1
                                if (bools1[t1]) {
                                    // set b to neighbor relationship between t2 and t1 given direction d
                                    // (if t2 and t1 can be neighbors in this direction, we stop searching!)
                                    foundValidNeighbor = prop[t1];
                                }
                            }

                            if (!foundValidNeighbor) {
                                // we didn't find any valid tiles for cell 1 if we put t2 in cell 2
                                // cannot have t2 in cell 2
                                bools2[t2] = false;
                                wave[x2][y2][z2] = bools2;

                                // we changed something in cell 2
                                changes[x2][y2][z2] = true;
                                change = true;
                            }
                        }
                    }

                } // end direction d loop
            } // end z2 loop
        } // end y2 loop
    } // end x2 loop

    return change;
}

bool WFC::findLowestEntropy(glm::vec3& cell, std::vector<int>& indices)
{
    // want to find lowest non-zero entropy cell
    // cell with one valid tile has zero entropy
    // cell with no valid tiles is contradiction
    bool allCellsAtZeroEntropy = true;
    int min = INT_MAX;

    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {

                std::vector<bool> bools = wave[x][y][z];
                int entropy = -1;
                std::vector<int> validTileIndices;
                for (int t = 0; t < actionCount; t++) {
                    if (bools[t]) {
                        // there is a valid tile for cell xyz
                        entropy++;
                        validTileIndices.push_back((t));
                    }
                }

                // use random noise to break entropy ties
                double noise = ((double) rand() / RAND_MAX) / 1000;
                if (entropy == -1) {
                    // something went wrong, not a single valid tile for cell xyz
                    // TODO: implement backtracking?
                    throw "no valid tiles for cell!";
                } else if (entropy > 0 && entropy + noise < min) {
                    // found new min entropy cell
                    min = entropy + noise;
                    cell = glm::vec3(x, y, z);
                    indices = validTileIndices;
                    allCellsAtZeroEntropy = false;
                }
            }
        }
    }

    // if all cells have zero entropy, WFC is complete
    if (allCellsAtZeroEntropy) {
        for (int x = 0; x < dim.x; x++) {
            for (int y = 0; y < dim.y; y++) {
                for (int z = 0; z < dim.z; z++) {
                    for (int t = 0; t < actionCount; t++) {
                        if (wave[x][y][z][t]) {
                            // indicate index of "observed" tile for each cell
                            observed[x][y][z] = t;
                            break;
                        }
                    }
                }
            }
        }
        return true;
    }

    return false;
}

void WFC::outputObservations(std::vector<std::vector<std::vector<Tile>>>* tiles) const {
    // TODO: fix this nonsense
    int xBound = dim.x;
    int yBound = dim.y;
    int zBound = dim.z;
    int observedIndexOffset = 0;

    if (sky) {
        xBound = dim.x - 2;
        yBound = dim.y - 2;
        zBound = dim.z - 2;
        observedIndexOffset = 1;
    }

    for (int x = 0; x < xBound; x++) {
        for (int y = 0; y < yBound; y++) {
            for (int z = 0; z < zBound; z++) {
                int tileIndex = observed[x + observedIndexOffset][y + observedIndexOffset][z + observedIndexOffset];
                Tile tile = Tile(context, tileset);

                std::string tileName = "empty";
                if (tileIndex != -1) {
                    tileName = tileNames[tileIndex].substr(0, tileNames[tileIndex].find(" "));
                }
                tile.setName(tileName);

                float offset = voxelSize / 2.f;

                glm::mat4 rotMat = glm::mat4();
                if (tileIndex != -1) {
                    rotMat = tileRotations[tileIndex];
                }
                tile.setTransform(getTileTransform(glm::vec3(x, y, z), rotMat));

                (*tiles)[x][y][z] = tile;
            }
        }
    }
}

void WFC::setDim(int x, int y, int z) {
    this->dim = glm::vec3(x, y, z);
}

void WFC::setTileset(std::string tileset) {
    tilesetChanged = this->tileset != tileset;
    this->tileset = tileset;
}

void WFC::setBuildIndices(std::vector<glm::vec3> buildIndices) {
    this->buildIndices = buildIndices;
}

float WFC::getVoxelSize() const {
    return this->voxelSize;
}

glm::mat4 WFC::getTileTransform(glm::vec3 pos, glm::mat4 rotMat) const {
    float offset = voxelSize / 2.f;

    glm::mat4 trans1Mat = glm::translate(glm::mat4(),
                                         glm::vec3(voxelSize * pos.x,
                                                   voxelSize * pos.y,
                                                   voxelSize * pos.z)
                                         + glm::vec3(offset));
    glm::mat4 scaleMat = glm::mat4();

    // MagicaVoxel places voxels on top of 0 in y-dir, not centered at 0
    glm::mat4 trans2Mat = glm::translate(glm::mat4(), glm::vec3(0, -offset, 0));

    glm::mat4 transformMat = trans1Mat * rotMat * scaleMat * trans2Mat;

    return transformMat;
}


