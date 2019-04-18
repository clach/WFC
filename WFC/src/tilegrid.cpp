#include "tilegrid.h"

TileGrid::TileGrid() : TileGrid(nullptr, "", 0, 0, 0)
{
}

TileGrid::TileGrid(GLWidget277 *context) : TileGrid(context, "", 0, 0, 0)
{
}

TileGrid::TileGrid(GLWidget277 *context, std::string tileset, int xDim, int yDim, int zDim) :
    dim(glm::vec3(xDim, yDim, zDim)), context(context), tileset(tileset)
{
    for (int x = 0; x < dim.x; x++) {
        std::vector<std::vector<Tile>> tilesY;
        for (int y = 0; y < dim.y; y++) {
            std::vector<Tile> tilesZ;
            for (int z = 0; z < dim.z; z++) {
                tilesZ.push_back(Tile(context, this, tileset));
            }
            tilesY.push_back(tilesZ);
        }
        tiles.push_back(tilesY);
    }
    wfc = new WFC(context);
    wfc->tileGrid = this;
}

TileGrid::~TileGrid() {
    // TODO
    delete wfc;
}

bool TileGrid::runWFC() {
    return wfc->run(&tiles);
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

glm::vec3 TileGrid::getDim() const {
    return dim;
}

void TileGrid::setDim(glm::vec3 dim, bool keepTiles, std::vector<glm::vec3> buildIndices) {
    this->dim = dim;

    std::vector<std::vector<std::vector<Tile>>> tilesCopy = tiles;

    // create new tiles array with new dimensions
    tiles.clear();
    for (int x = 0; x < dim.x; x++) {
        std::vector<std::vector<Tile>> tilesY;
        for (int y = 0; y < dim.y; y++) {
            std::vector<Tile> tilesZ;
            for (int z = 0; z < dim.z; z++) {
                tilesZ.push_back(Tile(context, this, tileset));
            }
            tilesY.push_back(tilesZ);
        }
        tiles.push_back(tilesY);
    }

    if (keepTiles) {
        // copy over original tiles
        int minX = std::min((int)dim.x, (int)tilesCopy.size());
        int minY = std::min((int)dim.y, (int)tilesCopy[0].size());
        int minZ = std::min((int)dim.z, (int)tilesCopy[0][0].size());

        for (int i = 0; i < buildIndices.size(); i++) {
            int x  = buildIndices[i].x;
            int y  = buildIndices[i].y;
            int z  = buildIndices[i].z;

            if (x < minX && y < minY && z < minZ) {
                tiles[x][y][z] = tilesCopy[x][y][z];
            }

        }
    }

    wfc->setBuildIndices(buildIndices);
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

float TileGrid::getVoxelSize() const {
    return wfc->getVoxelSize();
}

glm::mat4 TileGrid::getTileTransform(glm::vec3 pos, glm::mat4 rotMat) const {
    return wfc->getTileTransform(pos, rotMat);
}

void TileGrid::clear() {
    for (int x = 0; x < dim.x; x++) {
        for (int y = 0; y < dim.y; y++) {
            for (int z = 0; z < dim.z; z++) {
                Tile emptyTile = Tile(context, this, tileset);
                tiles[x][y][z] = emptyTile;
            }
        }
    }
}

void TileGrid::visualizeEmptyTiles(bool visualize) {
    this->visualize = visualize;
    // only done in build mode
    for (glm::vec3 buildIndex : wfc->getBuildIndices()) {
        Tile tile = tiles[buildIndex.x][buildIndex.y][buildIndex.z];
        if (tile.getName() == "empty") {
            tile.setVisualizeEmptyTiles(visualize);
        }
    }
}

bool TileGrid::visualizeEmptyTiles() const {
    return visualize;
}


