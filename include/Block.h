#ifndef BLOCK
#define BLOCK

#include <glm/glm.hpp>
#include <vector>
#include <utility>

#include "VkUtils.h"

using namespace VkUtils;

enum BlockType {AIR, GRASS, DIRT, LOG, LEAVES};

class Block {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    bool occupied = false;

    BlockType type = AIR;

    Block();
    Block(glm::vec3 blockPosition, BlockType blockType);

    void setType(BlockType blockType);

    void setTypeIfAir(BlockType blockType);

    void getVerticesIndices(std::vector<Vertex> &vertices, std::vector<uint32_t> &indices, 
        bool positiveXFaceVisible, bool negativeXFaceVisible,
        bool positiveYFaceVisible, bool negativeYFaceVisible,
        bool positiveZFaceVisible, bool negativeZFaceVisible);
};

#endif