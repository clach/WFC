#include "tilegrid.h"

TileGrid::TileGrid() : TileGrid(0, 0, 0)
{

}

TileGrid::TileGrid(int xDim, int yDim) : TileGrid(xDim, yDim, 0)
{

}

TileGrid::TileGrid(int xDim, int yDim, int zDim) :
    dim(glm::vec3(xDim, yDim, zDim)), tilesArr(new Tile[xDim * yDim * zDim])
{
    /*
    if (zDim != 0) {
        tiles.reserve(xDim * yDim * zDim);
        for (int i = 0; i < xDim * yDim * zDim; i++) {
            tiles.at(i) = new Tile();
        }
    } else {
        tiles.reserve(xDim * yDim);
        for (int i = 0; i < xDim * yDim; i++) {
            tiles.at(i) = new Tile();
        }
    }*/
}

TileGrid::~TileGrid() {

}

Tile* TileGrid::getTileAt(int x, int y) const {
    //return tileGrid.at(x * y);
    return nullptr;
}

Tile* TileGrid::getTileAt(int x, int y, int z) const {
    return tiles.at(x * dim[1] * dim[2] + y * dim[0] + z);
}

void TileGrid::setTileAt(Tile* tile, int x, int y) {
    //tileGrid.at()
}

void TileGrid::setTileAt(Tile* tile, int x, int y, int z) {
    tiles.at(x * dim[1] * dim[2] + y * dim[0] + z) = tile;
}

void TileGrid::createTiles() {
    for (Tile* t : tiles) {
        t->createTileMesh();
    }
}

void TileGrid::drawTiles(ShaderProgram& sp) {
    for (Tile* t : tiles) {
        t->drawTileMesh(sp);
    }
}

