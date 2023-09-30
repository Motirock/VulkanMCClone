#ifndef BLOCK
#define BLOCK

#include <glm/glm.hpp>
#include <vector>
#include <utility>

#include "VkUtils.h"

using namespace VkUtils;

enum BlockType {AIR, GRASS, DIRT, LOG, LEAVES, STONE, SNOW, SAND, WATER};

class Block {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    bool occupied = false;
    bool opaque = false;

    BlockType type = AIR;

    Block();
    Block(glm::vec3 blockPosition, BlockType blockType);
    ~Block();

    void updateOpacity();

    void setType(BlockType blockType);

    void setTypeIfAir(BlockType blockType);

    void getVerticesIndices(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, 
        bool positiveXFaceVisible, bool negativeXFaceVisible,
        bool positiveYFaceVisible, bool negativeYFaceVisible,
        bool positiveZFaceVisible, bool negativeZFaceVisible,
        std::vector<Vertex> &transluscentVertices, std::vector<uint32_t> &transluscentIndices, uint32_t &mainIndexCount);
};

#endif