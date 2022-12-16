//
// Created by kkeiper1103 on 11/11/22.
//

#ifndef MODULETHREE_SPHEREGEOMETRY_H
#define MODULETHREE_SPHEREGEOMETRY_H


#include "../GL/Mesh.h"

class SphereGeometry : public Mesh {
float radius;
int widthSegments, heightSegments;

public:
    SphereGeometry(float radius = 1.f, int widthSegments = 32, int heightSegments = 16);
};


#endif //MODULETHREE_SPHEREGEOMETRY_H
