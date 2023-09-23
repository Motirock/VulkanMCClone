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
        if (!getBlock(x, y, z).occupied) {
            getBlock(x, y, z) = block;
            occupied = true;
        }
    }
}

Chunk::~Chunk() {

}

Block& Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) {
    return blockGrid[x*CHUNK_Y_SIZE*CHUNK_Z_SIZE+y*CHUNK_Z_SIZE+z];
}

void Chunk::setBlock(uint32_t x, uint32_t y, uint32_t z, Block& block) {
    blockGrid[x*CHUNK_Y_SIZE*CHUNK_Z_SIZE+y*CHUNK_Z_SIZE+z] = block;
}

void Chunk::getVerticesIndices(
    Chunk &positiveXChunk, Chunk &negativeXChunk,
    Chunk &positiveYChunk, Chunk &negativeYChunk,
    Chunk &positiveZChunk, Chunk &negativeZChunk) {
    for (int x = 0; x < CHUNK_X_SIZE; x++) {
        for (int y = 0; y < CHUNK_Y_SIZE; y++) {
            for (int z = 0; z < CHUNK_Z_SIZE; z++) {
                if (!getBlock(x, y, z).occupied)
                    continue;
                getBlock(x, y, z).getVerticesIndices(vertices, indices,
                    (x == CHUNK_X_SIZE-1 && !(positiveXChunk.occupied && positiveXChunk.getBlock(0, y, z).occupied) && positiveXChunk.position.y != -1.0f)
                        || x+1 < CHUNK_X_SIZE && !(getBlock(x+1, y, z).occupied || getBlock(x+1, y, z).type == getBlock(x, y, z).type),
                    (x == 0 && !(negativeXChunk.occupied && negativeXChunk.getBlock(CHUNK_X_SIZE-1, y, z).occupied) && negativeXChunk.position.y != -1.0f) 
                        || x-1 >= 0 && !(getBlock(x-1, y, z).occupied || getBlock(x-1, y, z).type == getBlock(x, y, z).type),
                    (y == CHUNK_Y_SIZE-1 && !(positiveYChunk.occupied && positiveYChunk.getBlock(x, 0, z).occupied) && positiveYChunk.position.y != -1.0f)
                        || y+1 < CHUNK_Y_SIZE && !(getBlock(x, y+1, z).occupied || getBlock(x, y+1, z).type == getBlock(x, y, z).type),
                    (y == 0 && !(negativeYChunk.occupied && negativeYChunk.getBlock(x, CHUNK_Y_SIZE-1, z).occupied) && negativeYChunk.position.y != -1.0f)
                        || y-1 >= 0 && !(getBlock(x, y-1, z).occupied || getBlock(x, y-1, z).type == getBlock(x, y, z).type),
                    (z == CHUNK_Z_SIZE-1 && !(positiveZChunk.occupied && positiveZChunk.getBlock(x, y, 0).occupied) && positiveZChunk.position.y != -1.0f)
                        || z+1 < CHUNK_Z_SIZE && !(getBlock(x, y, z+1).occupied || getBlock(x, y, z+1).type == getBlock(x, y, z).type),
                    (z == 0 && !(negativeZChunk.occupied && negativeZChunk.getBlock(x, y, CHUNK_Z_SIZE-1).occupied) && negativeZChunk.position.y != -1.0f)
                        || z-1 >= 0 && !(getBlock(x, y, z-1).occupied || getBlock(x, y, z-1).type == getBlock(x, y, z).type));
            }
        }
    }
}