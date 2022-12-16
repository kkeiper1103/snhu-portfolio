//
// Created by kkeiper1103 on 11/11/22.
//

#ifndef MODULETHREE_PYRAMIDGEOMETRY_H
#define MODULETHREE_PYRAMIDGEOMETRY_H


#include "../GL/Mesh.h"

class PyramidGeometry : public Mesh {
private:
    float base = 0, height = 0;

public:
    PyramidGeometry(float base, float height);
};


#endif //MODULETHREE_PYRAMIDGEOMETRY_H
