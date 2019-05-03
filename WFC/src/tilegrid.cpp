#include "tilegrid.h"

TileGrid::TileGrid() : TileGrid(nullptr, "", 0, 0, 0)
{
}

TileGrid::TileGrid(GLWidget277 *context) : TileGrid(context, "", 0, 0, 0)
{
}

TileGrid::TileGrid(GLWidget277 *context, std::string tileset, int xDim, int yDim, int zDim) :
    context(context), dim(glm::vec3(xDim, yDim, zDim)), tileset(tileset), buildMode(false)
{
    std::vector<Tile> tilesZ(dim.z, Tile(context, tileset));
    std::vector<std::vector<Tile>> tilesY(dim.y, tilesZ);
    for (int x = 0; x < dim.x; x++) {
        tiles.push_back(tilesY);
    }

    wfc = new WFC(context);
}

TileGrid::~TileGrid() {
    // TODO
    delete wfc;
}

void TileGrid::setupWFC() {
    wfc->setup(&tiles);
}

bool TileGrid::runWFC() {
    return wfc->run(&tiles);
}

bool TileGrid::runWFCIteration(bool& done) {
    return wfc->runIteration(&tiles, done);
}

Tile TileGrid::getTileAt(int x, int y, int z) const {
    if (x < 0 || x >= dim.x || y < 0 || y >= dim.y || z < 0 || z >= dim.z) {
        // TODO: throw more meaningful error
        throw "out of bounds!";
    }
    return tiles[x][y][z];
}

void TileGrid::setTileAt(Tile tile, int x, int y, int z) {
    if (x < 0 || x >= dim.x || y < 0 || y >= dim.y || z < 0 || z >= dim.z) {
        // TODO: throw more meaningful error
        throw "out of bounds";
    }
    tiles[x][y][z] = tile;
}

void TileGrid::createTiles() {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                tiles[x][y][z].createTileMesh();
            }
        }
    }
}

void TileGrid::drawTiles(ShaderProgram& sp) {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                tiles[x][y][z].drawTileMesh(sp);
            }
        }
    }
}

void TileGrid::destroyTiles() {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                tiles[x][y][z].destroyTileMesh();
            }
        }
    }
}

std::string TileGrid::getTileset() const {
    return tileset;
}

glm::vec3 TileGrid::getDim() const {
    return dim;
}

void TileGrid::setDim(glm::vec3 dim, bool keepTiles, std::vector<glm::vec3>* buildIndices) {
    this->dim = dim;

    std::vector<std::vector<std::vector<Tile>>> tilesCopy = tiles;

    // create new tiles array with new dimensions
    tiles.clear();
    std::vector<Tile> tilesZ(dim.z, Tile(context, tileset));
    std::vector<std::vector<Tile>> tilesY(dim.y, tilesZ);
    for (int x = 0; x < dim.x; x++) {
        tiles.push_back(tilesY);
    }

    if (keepTiles) {
        // copy over original tiles
        int minX = std::min((int)dim.x, (int)tilesCopy.size());
        int minY = std::min((int)dim.y, (int)tilesCopy[0].size());
        int minZ = std::min((int)dim.z, (int)tilesCopy[0][0].size());

        std::vector<glm::vec3> buildIndicesToErase;
        for (int i = 0; i < buildIndices->size(); i++) {
            int x  = (*buildIndices)[i].x;
            int y  = (*buildIndices)[i].y;
            int z  = (*buildIndices)[i].z;

            if (x < minX && y < minY && z < minZ) {
                tiles[x][y][z] = tilesCopy[x][y][z];
            } else {
                buildIndicesToErase.push_back(glm::vec3(x, y, z));
            }
        }

        // remove all build indices that no longer fit in the grid dimensions
        for (glm::vec3 indices : buildIndicesToErase) {
            std::vector<glm::vec3>::iterator it = std::find(buildIndices->begin(), buildIndices->end(), indices);
            if (it != buildIndices->end()) {
                buildIndices->erase(it);
            }
        }
    }

    wfc->setBuildIndices(*buildIndices);
    wfc->setDim(dim.x, dim.y, dim.z);
}

void TileGrid::setTileset(std::string tileset) {
    this->tileset = tileset;
    wfc->setTileset(tileset);
}

void TileGrid::setPeriodic(bool periodic) {
    wfc->setPeriodic(periodic);
}

void TileGrid::setSky(bool sky) {
    wfc->setSky(sky);
}

void TileGrid::setBuildMode(bool buildMode) {
    this->buildMode = buildMode;
}


float TileGrid::getVoxelSize() const {
    return wfc->getVoxelSize();
}

int TileGrid::getMaxCardinality(std::string tileName) const {
    return wfc->getMaxCardinality(tileName);
}


glm::mat4 TileGrid::calculateTileTransform(glm::vec3 pos, int cardinality) const {
    return wfc->calculateTileTransform(pos, cardinality);
}

void TileGrid::clear() {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                Tile emptyTile = Tile(context, tileset);
                tiles[x][y][z] = emptyTile;
            }
        }
    }
}

void TileGrid::clearNonUserTiles(std::vector<glm::vec3> buildIndices) {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                glm::vec3 index = glm::vec3(x, y, z);
                if (std::find(buildIndices.begin(), buildIndices.end(), index) == buildIndices.end()) {
                    Tile emptyTile = Tile(context, tileset);
                    tiles[x][y][z] = emptyTile;
                }
            }
        }
    }
}



