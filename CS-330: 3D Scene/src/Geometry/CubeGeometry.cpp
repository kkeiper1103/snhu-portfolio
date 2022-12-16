//
// Created by kkeiper1103 on 11/11/22.
//

#include "CubeGeometry.h"

CubeGeometry::CubeGeometry(float width, float height, float depth) : Mesh({}, {}), width(width), height(height), depth(depth) {
    std::vector<Vertex> vertices {
        {(width / 2), (height / 2), (depth / 2), 1.0f, 0.0f, 0.0f, 1.0f, 1, 1}, // Top Right Vertex 0
        {(width / 2), -(height / 2), (depth / 2), 0.0f, 1.0f, 0.0f, 1.0f, 1, 0}, // Bottom Right Vertex 1
        {-(width / 2), -(height / 2), (depth / 2), 0.0f, 0.0f, 1.0f, 1.0f, 0, 0}, // Bottom Left Vertex 2
        {-(width / 2), (height / 2), (depth / 2), 1.0f, 0.0f, 1.0f, 1.0f, 0, 1}, // Top Left Vertex 3

        {(width / 2), -(height / 2), -(depth / 2), 0.5f, 0.5f, 1.0f, 1.0f, 1, 1}, // 4 br  right
        {(width / 2), (height / 2), -(depth / 2), 1.0f, 1.0f, 0.5f, 1.0f, 1, 0}, //  5 tl  right
        {-(width / 2), (height / 2), -(depth / 2), 0.2f, 0.2f, 0.5f, 1.0f, 0, 0}, //  6 tl  top
        {-(width / 2), -(height / 2), -(depth / 2), 1.0f, 0.0f, 1.0f, 1.0f, 0, 1}  //  7 bl back
    };

    std::vector<GLushort> indices {
            0, 1, 3,  // Triangle 1
            1, 2, 3,   // Triangle 2
            0, 1, 4,  // Triangle 3
            0, 4, 5,  // Triangle 4
            0, 5, 6, // Triangle 5
            0, 3, 6,  // Triangle 6
            4, 5, 6, // Triangle 7
            4, 6, 7, // Triangle 8
            2, 3, 6, // Triangle 9
            2, 6, 7, // Triangle 10
            1, 4, 7, // Triangle 11
            1, 2, 7 // Triangle 12
    };

    // since vertices are shared between indices, I'm not sure if this is right.
    // I probably want to generate a list of vertices from 0..n

    for(auto i=0; i < indices.size() - 3; i+=3) {
        auto &v1 = vertices[indices[i]],
            &v2 = vertices[indices[i+1]],
            &v3 = vertices[indices[i+2]];

        auto normal = glm::triangleNormal(v1.position, v2.position, v3.position);

        v1.normal = v2.normal = v3.normal = normal;
    }

    setData(vertices, indices);
}
