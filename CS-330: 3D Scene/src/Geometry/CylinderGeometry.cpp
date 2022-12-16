//
// Created by kkeiper1103 on 11/11/22.
//

#include "CylinderGeometry.h"

#include <easylogging++.h>
#include <numeric>

/**
 * Logic pulled from three.js CylinderGeometry.js
 * @param radiusTop
 * @param radiusBottom
 * @param height
 * @param radialSegments
 * @param heightSegments
 * @param openEnded
 * @param thetaStart
 * @param thetaLength
 */
CylinderGeometry::CylinderGeometry(double radiusTop, double radiusBottom, double height, int radialSegments,
                                   int heightSegments, bool openEnded, double thetaStart, double thetaLength) :
radiusTop(radiusTop), radiusBottom(radiusBottom), height(height), radialSegments(radialSegments), heightSegments(heightSegments),
openEnded(openEnded), thetaStart(thetaStart), thetaLength(thetaLength) {
    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;


    generateTorso(&vertices, &indices);

    if(radiusTop > 0)
        generateCap(true, &vertices, &indices);

    if(radiusBottom > 0)
        generateCap(false, &vertices, &indices);


    setData(vertices, indices);
}

void CylinderGeometry::generateTorso(std::vector<Vertex> *vertices, std::vector<GLushort> *indices) {

    index = 0;
    std::vector< std::vector<GLushort> > indexArray;
    auto halfHeight = height / 2;
    auto slope = ( radiusBottom - radiusTop ) / height;

    for(int y=0; y <= heightSegments; y++) {
        std::vector<GLushort> indexRow;

        double v = (double) y / heightSegments;
        double _radius = v * (radiusBottom - radiusTop) + radiusTop;


        for(int x =0; x <= radialSegments; x++) {
            double u = (double) x / radialSegments;
            double theta = u * thetaLength + thetaStart;

            double sinTheta = sin(theta);
            double cosTheta = cos(theta);

            vertices->push_back(Vertex {
                                        static_cast<float>(_radius * sinTheta),
                                        static_cast<float>(-v * height + halfHeight),
                                        static_cast<float>(_radius * cosTheta),
                                        0.f, 0.f, 0.f, 0.f,
                                        static_cast<float>(u),
                                        static_cast<float>(1 - v)
                                });

            indexRow.push_back(index++);
        }

        indexArray.push_back(indexRow);
    }

    // generate indices
    for(int x = 0; x < radialSegments; x++) {
        for(int y = 0; y < heightSegments; y++) {

            auto a = indexArray[y][x],
                    b = indexArray[y + 1][x],
                    c = indexArray[y + 1][ x + 1],
                    d = indexArray[y][x+1];

            indices->push_back(a);
            indices->push_back(b);
            indices->push_back(d);

            indices->push_back(b);
            indices->push_back(c);
            indices->push_back(d);
        }
    }
}

void CylinderGeometry::generateCap(bool top, std::vector<Vertex> *vertices, std::vector<GLushort> *indices) {
    // save the index of the first center vertex
    auto centerIndexStart = index;

    const auto radius = top ? radiusTop : radiusBottom;
    const auto sign = top ? 1 : - 1;
    const auto halfHeight = height / 2;

    // first we generate the center vertex data of the cap.
    // because the geometry needs one set of uvs per face,
    // we must generate a center vertex per face/segment

    for ( auto x = 1; x <= radialSegments; x ++ ) {

        // vertex

        vertices->push_back( {
            0, static_cast<float>(halfHeight * sign), 0, 1, 1, 1, 1, .5, .5
        } );

        // increase index
        index++;
    }

    // save the index of the last center vertex
    const auto centerIndexEnd = index;

    // now we generate the surrounding vertices, normals and uvs

    for ( auto x = 0; x <= radialSegments; x ++ ) {

        const auto u = x / radialSegments;
        const auto theta = u * thetaLength + thetaStart;

        const auto cosTheta = cos( theta );
        const auto sinTheta = sin( theta );

        // vertex
        vertices->push_back({
            static_cast<float>(radius * sinTheta),
            static_cast<float>(halfHeight * sign),
            static_cast<float>(radius * cosTheta),
            1, 1, 1, 1,
            static_cast<float>(( cosTheta * 0.5 ) + 0.5),
            static_cast<float>(( sinTheta * 0.5 * sign ) + 0.5)
        });

        // increase index
        index++;
    }

    // generate indices

    for ( auto x = 0; x < radialSegments; x ++ ) {

        const auto c = centerIndexStart + x;
        const auto i = centerIndexEnd + x;

        if ( top ) {

            // face top
            indices->push_back( i );
            indices->push_back( i + 1 );
            indices->push_back( c );

        } else {

            // face bottom
            indices->push_back( i + 1 );
            indices->push_back( i );
            indices->push_back( c );
        }
    }
}

