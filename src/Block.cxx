#include "Block.h"
#include <iostream>

Block::Block() {
    position = glm::vec3(0.0f);
}

Block::Block(glm::vec3 blockPosition, BlockType blockType) : position(blockPosition), type(blockType) {
    occupied = type != AIR;
}

Block::~Block() {

}

void Block::setType(BlockType blockType) {
    type = blockType;
    occupied = type != AIR;
}

void Block::setTypeIfAir(BlockType blockType) {
    if (type == AIR) {
        type = blockType;
        occupied = true;
    }
}

void Block::getVerticesIndices(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, 
    bool positiveXFaceVisible, bool negativeXFaceVisible,
    bool positiveYFaceVisible, bool negativeYFaceVisible,
    bool positiveZFaceVisible, bool negativeZFaceVisible) {
    if (!occupied)
        return;

    uint32_t currentIndex = vertices.size();

    glm::vec3 sideColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 topColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec2 sideTextureCoords = glm::vec2(0.0f, 0.0f);
    glm::vec2 topTextureCoords = glm::vec2(0.0f, 0.0f);
    glm::vec2 bottomTextureCoords = glm::vec2(0.0f, 0.0f);

    switch (type) {
        case DIRT:
            sideTextureCoords.x = (2.0f/16.0f);
            sideTextureCoords.y = (0.0f/16.0f);
            topTextureCoords.x = sideTextureCoords.x;
            topTextureCoords.y = sideTextureCoords.y;
            bottomTextureCoords.x = sideTextureCoords.x;
            bottomTextureCoords.y = sideTextureCoords.y;
            break;
        case GRASS:
            topColor = glm::vec3(0.25f, 0.9f, 0.15f);
            sideTextureCoords.x = (3.0f/16.0f);
            sideTextureCoords.y = (0.0f/16.0f);
            topTextureCoords.x = (0.0f/16.0f);
            topTextureCoords.y = (0.0f/16.0f);
            bottomTextureCoords.x = sideTextureCoords.x;
            bottomTextureCoords.y = sideTextureCoords.y;
            break;
        case LOG:
            sideTextureCoords.x = (4.0f/16.0f);
            sideTextureCoords.y = (1.0f/16.0f);
            topTextureCoords.x = (5.0f/16.0f);
            topTextureCoords.y = (1.0f/16.0f);
            bottomTextureCoords.x = topTextureCoords.x;
            bottomTextureCoords.y = topTextureCoords.y;
            break;
        case LEAVES:
            sideColor = glm::vec3(0.0f, 0.9f, 0.05f);
            topColor = sideColor;
            sideTextureCoords.x = (4.0f/16.0f);
            sideTextureCoords.y = (3.0f/16.0f);
            topTextureCoords.x = sideTextureCoords.x;
            topTextureCoords.y = sideTextureCoords.y;
            bottomTextureCoords.x = sideTextureCoords.x;
            bottomTextureCoords.y = sideTextureCoords.y;
            break;
        case STONE:
            sideTextureCoords.x = (1.0f/16.0f);
            sideTextureCoords.y = (0.0f/16.0f);
            topTextureCoords.x = sideTextureCoords.x;
            topTextureCoords.y = sideTextureCoords.y;
            bottomTextureCoords.x = sideTextureCoords.x;
            bottomTextureCoords.y = sideTextureCoords.y;
            break;
        case SNOW:
            sideTextureCoords.x = (2.0f/16.0f);
            sideTextureCoords.y = (4.0f/16.0f);
            topTextureCoords.x = sideTextureCoords.x;
            topTextureCoords.y = sideTextureCoords.y;
            bottomTextureCoords.x = sideTextureCoords.x;
            bottomTextureCoords.y = sideTextureCoords.y;
            break;
             
        case AIR:
            occupied = false;
            return;
            break;
    }
    
    //Positive x face
    if (positiveXFaceVisible) {
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 3);
        currentIndex += 4;
    }

    //Negative x face
    if (negativeXFaceVisible) {
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 1);
        currentIndex += 4;
    }

    //Positive y face
    if (positiveYFaceVisible) {
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 1);
        currentIndex += 4;
    }

    //Negative y face
    if (negativeYFaceVisible) {
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z+0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z-0.5}, sideColor, sideTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 3);
        currentIndex += 4;
    }

    //Positive z face
    if (positiveZFaceVisible) {
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z+0.5}, topColor, topTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z+0.5}, topColor, topTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z+0.5}, topColor, topTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z+0.5}, topColor, topTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 3);
        currentIndex += 4;
    }

    //Negative z face
    if (negativeZFaceVisible) {
        vertices.emplace_back(Vertex{{position.x+0.5, position.y+0.5, position.z-0.5}, sideColor, bottomTextureCoords+glm::vec2(1.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y+0.5, position.z-0.5}, sideColor, bottomTextureCoords+glm::vec2(0.0f, 0.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x-0.5, position.y-0.5, position.z-0.5}, sideColor, bottomTextureCoords+glm::vec2(0.0f, 1.0f)/16.0f});
        vertices.emplace_back(Vertex{{position.x+0.5, position.y-0.5, position.z-0.5}, sideColor, bottomTextureCoords+glm::vec2(1.0f, 1.0f)/16.0f});
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 1);
        indices.emplace_back(currentIndex + 0);
        indices.emplace_back(currentIndex + 3);
        indices.emplace_back(currentIndex + 2);
        indices.emplace_back(currentIndex + 1);
        currentIndex += 4;
    }
}