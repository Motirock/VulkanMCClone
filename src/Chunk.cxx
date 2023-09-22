#include "Chunk.h"
#include <iostream>

Chunk::Chunk() {
    throw std::runtime_error("ERROR: Created Chunk using default constructor!");
};

Chunk::Chunk(glm::vec3 chunkPosition, std::vector<Block> &blocks) : position(chunkPosition) {
    for (Block &block : blocks) {
        int x = std::fmod(block.position.x, CHUNK_X_SIZE);
        int y = std::fmod(block.position.y, CHUNK_Y_SIZE);
        int z = std::fmod(block.position.z, CHUNK_Z_SIZE);
        if (!blockGrid[x][y][z].occupied) {
            blockGrid[x][y][z] = block;
            occupied = true;
        }
    }
}

Chunk::~Chunk() {

}

void Chunk::getVerticesIndices(
    Chunk &positiveXChunk, Chunk &negativeXChunk,
    Chunk &positiveYChunk, Chunk &negativeYChunk,
    Chunk &positiveZChunk, Chunk &negativeZChunk) {
    for (int x = 0; x < CHUNK_X_SIZE; x++) {
        for (int y = 0; y < CHUNK_Y_SIZE; y++) {
            for (int z = 0; z < CHUNK_Z_SIZE; z++) {
                if (!blockGrid[x][y][z].occupied)
                    continue;
                blockGrid[x][y][z].getVerticesIndices(vertices, indices,
                    (x == CHUNK_X_SIZE-1 && !(positiveXChunk.occupied && positiveXChunk.blockGrid[0][y][z].occupied) && positiveXChunk.position.y != -1.0f)
                        || x+1 < CHUNK_X_SIZE && !(blockGrid[x+1][y][z].occupied || blockGrid[x+1][y][z].type == blockGrid[x][y][z].type),
                    (x == 0 && !(negativeXChunk.occupied && negativeXChunk.blockGrid[CHUNK_X_SIZE-1][y][z].occupied) && negativeXChunk.position.y != -1.0f) 
                        || x-1 >= 0 && !(blockGrid[x-1][y][z].occupied || blockGrid[x-1][y][z].type == blockGrid[x][y][z].type),
                    (y == CHUNK_Y_SIZE-1 && !(positiveYChunk.occupied && positiveYChunk.blockGrid[x][0][z].occupied) && positiveYChunk.position.y != -1.0f)
                        || y+1 < CHUNK_Y_SIZE && !(blockGrid[x][y+1][z].occupied || blockGrid[x][y+1][z].type == blockGrid[x][y][z].type),
                    (y == 0 && !(negativeYChunk.occupied && negativeYChunk.blockGrid[x][CHUNK_Y_SIZE-1][z].occupied) && negativeYChunk.position.y != -1.0f)
                        || y-1 >= 0 && !(blockGrid[x][y-1][z].occupied || blockGrid[x][y-1][z].type == blockGrid[x][y][z].type),
                    (z == CHUNK_Z_SIZE-1 && !(positiveZChunk.occupied && positiveZChunk.blockGrid[x][y][0].occupied) && positiveZChunk.position.y != -1.0f)
                        || z+1 < CHUNK_Z_SIZE && !(blockGrid[x][y][z+1].occupied || blockGrid[x][y][z+1].type == blockGrid[x][y][z].type),
                    (z == 0 && !(negativeZChunk.occupied && negativeZChunk.blockGrid[x][y][CHUNK_Z_SIZE-1].occupied) && negativeZChunk.position.y != -1.0f)
                        || z-1 >= 0 && !(blockGrid[x][y][z-1].occupied || blockGrid[x][y][z-1].type == blockGrid[x][y][z].type));
            }
        }
    }
}