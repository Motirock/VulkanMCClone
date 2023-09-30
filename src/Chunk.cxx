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
            if (block.type != AIR) {
                occupied = true;
            }
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

void Chunk::loadVerticesIndices(
    Chunk &positiveXChunk, Chunk &negativeXChunk,
    Chunk &positiveYChunk, Chunk &negativeYChunk,
    Chunk &positiveZChunk, Chunk &negativeZChunk,
    std::vector<Vertex> &transluscentVertices, std::vector<uint32_t> &transluscentIndices, uint32_t &mainIndexCount) {
    vertices.clear();
    indices.clear();

    for (int x = 0; x < CHUNK_X_SIZE; x++) {
        for (int y = 0; y < CHUNK_Y_SIZE; y++) {
            for (int z = 0; z < CHUNK_Z_SIZE; z++) {
                if (!getBlock(x, y, z).occupied)
                    continue;
                getBlock(x, y, z).getVerticesIndices(vertices, indices,
                    (x == CHUNK_X_SIZE-1 && positiveXChunk.position.y != -1.0f && (!positiveXChunk.occupied || (!positiveXChunk.getBlock(0, y, z).opaque && positiveXChunk.getBlock(0, y, z).type != getBlock(x, y, z).type)))
                        || x+1 < CHUNK_X_SIZE && !(getBlock(x+1, y, z).opaque || getBlock(x+1, y, z).type == getBlock(x, y, z).type),
                    (x == 0 && negativeXChunk.position.y != -1.0f && (!negativeXChunk.occupied || (!negativeXChunk.getBlock(CHUNK_X_SIZE-1, y, z).opaque && negativeXChunk.getBlock(CHUNK_X_SIZE-1, y, z).type != getBlock(x, y, z).type))) 
                        || x-1 >= 0 && !(getBlock(x-1, y, z).opaque || getBlock(x-1, y, z).type == getBlock(x, y, z).type),
                    (y == CHUNK_Y_SIZE-1 && positiveYChunk.position.y != -1.0f && (!positiveYChunk.occupied || (!positiveYChunk.getBlock(x, 0, z).opaque && positiveYChunk.getBlock(x, 0, z).type != getBlock(x, y, z).type)))
                        || y+1 < CHUNK_Y_SIZE && !(getBlock(x, y+1, z).opaque || getBlock(x, y+1, z).type == getBlock(x, y, z).type),
                    (y == 0 && negativeYChunk.position.y != -1.0f && (!negativeYChunk.occupied || (!negativeYChunk.getBlock(x, CHUNK_Y_SIZE-1, z).opaque && negativeYChunk.getBlock(x, CHUNK_Y_SIZE-1, z).type != getBlock(x, y, z).type)))
                        || y-1 >= 0 && !(getBlock(x, y-1, z).opaque || getBlock(x, y-1, z).type == getBlock(x, y, z).type),
                    (z == CHUNK_Z_SIZE-1 && positiveZChunk.position.y != -1.0f && (!positiveZChunk.occupied || (!positiveZChunk.getBlock(x, y, 0).opaque && positiveZChunk.getBlock(x, y, 0).type != getBlock(x, y, z).type)))
                        || z+1 < CHUNK_Z_SIZE && !(getBlock(x, y, z+1).opaque || getBlock(x, y, z+1).type == getBlock(x, y, z).type),
                    (z == 0 && negativeZChunk.position.y != -1.0f && (!negativeZChunk.occupied || (!negativeZChunk.getBlock(x, y, CHUNK_Z_SIZE-1).opaque && negativeZChunk.getBlock(x, y, CHUNK_Z_SIZE-1).type != getBlock(x, y, z).type)))
                        || z-1 >= 0 && !(getBlock(x, y, z-1).opaque || getBlock(x, y, z-1).type == getBlock(x, y, z).type),
                    transluscentVertices, transluscentIndices, mainIndexCount);
            }
        }
    }
    blocksChanged = false;
}

bool Chunk::isVisible(glm::vec3 &cameraPos, glm::vec3 &viewDirection) {
    return vertices.size() > 0;
}