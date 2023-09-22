#ifndef CHUNK
#define CHUNK

#include "Block.h"

const int CHUNK_X_SIZE = 32;
const int CHUNK_Y_SIZE = 32;
const int CHUNK_Z_SIZE = 32;

class Chunk {
public:
    bool occupied = false;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    void *vertexData;
    void *indexData;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    Block blockGrid[CHUNK_X_SIZE][CHUNK_Y_SIZE][CHUNK_Z_SIZE];

    Chunk();
    Chunk(glm::vec3 chunkPosition, std::vector<Block> &blocks);
    ~Chunk();

    //bool (&negativeXFaces)[CHUNK_Y_SIZE][CHUNK_Z_SIZE])
    void getVerticesIndices(  
        Chunk &positiveXChunk, Chunk &negativeXChunk,
        Chunk &positiveYChunk, Chunk &negativeYChunk,
        Chunk &positiveZChunk, Chunk &negativeZChunk);
};

#endif