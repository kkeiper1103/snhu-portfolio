//
// Created by kkeiper1103 on 11/5/22.
//

#ifndef MODULETWO_VERTEX_H
#define MODULETWO_VERTEX_H

// replace with glm for ease of use (mostly for calculating normals)
#include <glm/glm.hpp>

struct Vertex {
    Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texture, glm::vec3 normal) :
    position(position),
    color(color),
    texture(texture),
    normal(normal) {}

    Vertex(float x, float y, float z) :
    Vertex(x, y, z, 0, 0, 0, 0) {}

    Vertex(float x, float y, float z, float r, float g, float b, float a) :
    Vertex(x, y, z, r, g, b, a, 0, 0) {}

    Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v) :
    Vertex(x, y, z, r, g, b, a, u, v, 0, 0, 0) {}

    Vertex(float x, float y, float z, float r, float g, float b, float a, float u, float v, float nx, float ny, float nz) :
    Vertex({x, y, z}, {r, g, b, a}, {u, v}, {nx, ny, nz}) {}

    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texture;
    glm::vec3 normal;
};

#endif //MODULETWO_VERTEX_H
