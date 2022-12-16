//
// Created by kkeiper1103 on 11/11/22.
//

#include "SphereGeometry.h"
#include <easylogging++.h>
#include <numeric>

/**
 * Much of the logic here is pulled from three js's logic for constructing a sphere geometry
 * MUCH HELP
 *
 * https://github.com/mrdoob/three.js/blob/master/src/geometries/SphereGeometry.js
 *
 * @param radius
 * @param widthSegments
 * @param heightSegments
 */
SphereGeometry::SphereGeometry(float radius, int widthSegments, int heightSegments) :
Mesh({}, {}), radius(radius), widthSegments(widthSegments), heightSegments(heightSegments) {
    double phiStart = 0,
        phiLength = M_PI * 2,
        thetaStart = 0,
        thetaLength = M_PI;

    widthSegments = std::max(2, widthSegments);
    heightSegments = std::max(3, heightSegments);

    const double thetaEnd = std::min(thetaStart + thetaLength, M_PI);
    GLushort index = 0;


    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;

    std::vector<std::vector<GLushort>> grid;

    for(int iy = 0; iy <= heightSegments; iy++) {
        double v = (double) iy / heightSegments;
        std::vector<GLushort> verticesRow;

        //
        double uOffset = 0.f;
        if(iy == 0 && thetaStart == 0) {
            uOffset = 0.5 / (double) widthSegments;
        }
        else if(iy == heightSegments && thetaEnd == M_PI) {
            uOffset = -.5 / (double) widthSegments;
        }

        for(int ix =0; ix <= widthSegments; ix++) {
            double u = (double) ix / widthSegments;

            float
                x = -radius * cos(phiStart + u * phiLength) * sin(thetaStart + v * thetaLength),
                y = radius * cos(thetaStart + v * thetaLength),
                z = radius * sin(phiStart + u * phiLength) * sin(thetaStart + v * thetaLength);

            vertices.push_back({
                x, y, z,
                1, 1, 1, 1,
                (float)(u + uOffset), (float)(1 - v)
            });

            verticesRow.push_back(index++);
        }

        grid.push_back(verticesRow);
    }

    // build the indices array
    for(int iy=0; iy < heightSegments; iy++) {

        for(int ix =0; ix <= widthSegments; ix++) {

            const GLushort a = grid[iy][ix + 1],
                b = grid[iy][ix],
                c = grid[iy + 1][ix],
                d = grid[iy + 1][ix + 1];

            if(iy != 0 || thetaStart > 0 ) {
                indices.push_back(a);
                indices.push_back(b);
                indices.push_back(d);
            }

            if(iy != heightSegments - 1 || thetaEnd < M_PI ) {
                indices.push_back(b);
                indices.push_back(c);
                indices.push_back(d);
            }
        }
    }

    setData(vertices, indices);
}
