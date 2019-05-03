#include "tilegridrepeater.h"

TileGridRepeater::TileGridRepeater()
{}

TileGridRepeater::TileGridRepeater(GLWidget277 *context, int numCopies) :
    context(context), numCopies(numCopies)
{}

TileGridRepeater::~TileGridRepeater()
{}

void TileGridRepeater::setTileGrid(const TileGrid& tileGrid) {
    // set up tiles grid of correct size
    tiles.clear();
    dim = tileGrid.getDim();
    tileset = tileGrid.getTileset();
    std::vector<Tile> tilesZ(dim.z * numCopies, Tile(context, tileset));
    std::vector<std::vector<Tile>> tilesY(dim.y * numCopies, tilesZ);
    for (int x = 0; x < dim.x * numCopies; x++) {
        tiles.push_back(tilesY);
    }

    // TODO: I think this is buggy
    for (int x = 0; x < dim.x * numCopies; x++) {
        for (int y = 0; y < dim.y * numCopies; y++) {
            for (int z = 0; z < dim.z * numCopies; z++) {
                // actually want to go backwards in z
                int posZ = z;
                if (posZ >= dim.z) {
                    posZ = dim.z - (posZ + 1);
                }

                Tile tile = tiles[x][y][z];
                if (x < dim.x && y < dim.y && z < dim.z) {
                    tile.setName("empty");
                    tile.setTransform(tileGrid.calculateTileTransform(glm::vec3(x, y, posZ), tile.getCardinality()));
                    tiles[x][y][z] = tile;
                } else {
                    int newX = x % (int)dim.x;
                    int newY = y % (int)dim.y;
                    int newZ = std::abs(posZ) % (int)dim.z;
                    Tile tile2 = tileGrid.getTileAt(newX, newY, newZ);
                    tile = tile2;
                }
                tile.setTransform(tileGrid.calculateTileTransform(glm::vec3(x, y, posZ), tile.getCardinality()));
                tiles[x][y][z] = tile;

            }
        }
    }
}


void TileGridRepeater::createTiles() {
    for (int x = 0; x < dim.x * numCopies; x++) {
        for (int y = 0; y < dim.y * numCopies; y++) {
            for (int z = 0; z < dim.z * numCopies; z++) {
                tiles[x][y][z].createTileMesh();
            }
        }
    }
}

void TileGridRepeater::drawTiles(ShaderProgram& sp) {
    for (int x = 0; x < dim.x * numCopies; x++) {
        for (int y = 0; y < dim.y * numCopies; y++) {
            for (int z = 0; z < dim.z * numCopies; z++) {
                tiles[x][y][z].drawTileMesh(sp);
            }
        }
    }
}

void TileGridRepeater::destroyTiles() {
    for (int x = 0; x < dim.x * numCopies; x++) {
        for (int y = 0; y < dim.y * numCopies; y++) {
            for (int z = 0; z < dim.z * numCopies; z++) {
                tiles[x][y][z].destroyTileMesh();
            }
        }
    }
}

void TileGridRepeater::clear() {
    for (int x = 0; x < dim.x * numCopies; x++) {
        for (int y = 0; y < dim.y * numCopies; y++) {
            for (int z = 0; z < dim.z * numCopies; z++) {
                Tile emptyTile = Tile(context, tileset);
                tiles[x][y][z] = emptyTile;
            }
        }
    }
}
