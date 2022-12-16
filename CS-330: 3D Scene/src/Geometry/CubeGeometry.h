//
// Created by kkeiper1103 on 11/11/22.
//

#ifndef MODULETHREE_CUBEGEOMETRY_H
#define MODULETHREE_CUBEGEOMETRY_H


#include "../GL/Mesh.h"

class CubeGeometry : public Mesh {
float width = 1, height = 1, depth = 1;

public:
    explicit CubeGeometry(float width = 1.f, float height = 1.f, float depth = 1.f);
};


#endif //MODULETHREE_CUBEGEOMETRY_H
