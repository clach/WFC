#include "tilegrid.h"

TileGrid::TileGrid() : TileGrid(nullptr, "", 1, 0, 0, 0)
{
}

TileGrid::TileGrid(GLWidget277 *context, std::string tileset, int voxelSize, int xDim, int yDim, int zDim) :
    dim(glm::vec3(xDim, yDim, zDim)), context(context), tileset(tileset), voxelSize(voxelSize)
{
    for (int x = 0; x < dim.x; x++) {
        std::vector<std::vector<Tile>> tilesY;
        for (int y = 0; y < dim.y; y++) {
            std::vector<Tile> tilesZ;
            for (int z = 0; z < dim.z; z++) {
                tilesZ.push_back(Tile(context, tileset));
            }
            tilesY.push_back(tilesZ);
        }
        tiles.push_back(tilesY);
    }
}

TileGrid::~TileGrid() {
    // TODO
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

float TileGrid::getVoxelSize() const {
    return voxelSize;
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
