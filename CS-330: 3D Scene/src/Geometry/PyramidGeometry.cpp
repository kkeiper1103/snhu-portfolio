//
// Created by kkeiper1103 on 11/11/22.
//

#include "PyramidGeometry.h"

PyramidGeometry::PyramidGeometry(float base, float height) : Mesh({}, {}), base(base), height(height) {
    std::vector<Vertex> vertices = {
            Vertex {0, height, 0, 1, 1, 1, 1}, // top corner
            Vertex {-(base / 2), 0, -(base / 2), 1, 0, 1, 1}, // back left corner
            Vertex {-(base / 2), 0, (base / 2), 1, 1, 0, 1}, // front left corner
            Vertex {(base / 2), 0, (base / 2), 0, 0, 1, 1}, // front right corner
            Vertex {(base / 2), 0, -(base / 2), 0, 1, 1, 1}, // back right corner
    };

    // I just played around with guessing which vertices needed combined until I got it. it was all trial and error here
    std::vector<GLushort> indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
        4, 1, 2,
        4, 2, 3,
    };

    setData(vertices, indices);
}
