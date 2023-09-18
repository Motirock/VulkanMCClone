#include "Chunk.h"

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

void Chunk::getVerticesIndices(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices,  
    Chunk &positiveXChunk, Chunk &negativeXChunk,
    Chunk &positiveYChunk, Chunk &negativeYChunk,
    Chunk &positiveZChunk, Chunk &negativeZChunk) {
    for (int x = 0; x < CHUNK_X_SIZE; x++) {
        for (int y = 0; y < CHUNK_Y_SIZE; y++) {
            for (int z = 0; z < CHUNK_Z_SIZE; z++) {
                blockGrid[x][y][z].getVerticesIndices(vertices, indices,
                    (x == CHUNK_X_SIZE-1 && !(positiveXChunk.occupied && positiveXChunk.blockGrid[0][y][z].occupied))
                        || x+1 < CHUNK_X_SIZE && !blockGrid[x+1][y][z].occupied,
                    (x == 0 && !(negativeXChunk.occupied && negativeXChunk.blockGrid[CHUNK_X_SIZE-1][y][z].occupied)) 
                        || x-1 >= 0 && !blockGrid[x-1][y][z].occupied,
                    (y == CHUNK_Y_SIZE-1 && !(positiveYChunk.occupied && positiveYChunk.blockGrid[x][0][z].occupied))
                        || y+1 < CHUNK_Y_SIZE && !blockGrid[x][y+1][z].occupied,
                    (y == 0 && !(negativeYChunk.occupied && negativeYChunk.blockGrid[x][CHUNK_Y_SIZE-1][z].occupied))
                        || y-1 >= 0 && !blockGrid[x][y-1][z].occupied,
                    (z == CHUNK_Z_SIZE-1 && !(positiveZChunk.occupied && positiveZChunk.blockGrid[x][y][0].occupied))
                        || z+1 < CHUNK_Z_SIZE && !blockGrid[x][y][z+1].occupied,
                    (z == 0 && !(negativeZChunk.occupied && negativeZChunk.blockGrid[x][y][CHUNK_Z_SIZE-1].occupied))
                        || z-1 >= 0 && !blockGrid[x][y][z-1].occupied);
            }
        }
    }
}