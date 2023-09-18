#ifndef CHUNK
#define CHUNK

#include "Block.h"

const int CHUNK_X_SIZE = 16;
const int CHUNK_Y_SIZE = 16;
const int CHUNK_Z_SIZE = 16;

class Chunk {
public:
    bool occupied = false;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    Block blockGrid[CHUNK_X_SIZE][CHUNK_Y_SIZE][CHUNK_Z_SIZE];

    Chunk(glm::vec3 chunkPosition, std::vector<Block> &blocks);
    ~Chunk();

    //bool (&negativeXFaces)[CHUNK_Y_SIZE][CHUNK_Z_SIZE])
    void getVerticesIndices(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices,  
        Chunk &positiveXChunk, Chunk &negativeXChunk,
        Chunk &positiveYChunk, Chunk &negativeYChunk,
        Chunk &positiveZChunk, Chunk &negativeZChunk);
};

#endif