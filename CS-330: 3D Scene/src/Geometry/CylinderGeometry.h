//
// Created by kkeiper1103 on 11/11/22.
//

#ifndef MODULETHREE_CYLINDERGEOMETRY_H
#define MODULETHREE_CYLINDERGEOMETRY_H


#include "../GL/Mesh.h"

class CylinderGeometry : public Mesh {
double radiusTop, radiusBottom, height;
int radialSegments, heightSegments;
bool openEnded;
double thetaStart, thetaLength;

//
int index = 0;

void generateTorso( std::vector<Vertex>* vertices, std::vector<GLushort>* indices );
void generateCap( bool top, std::vector<Vertex>* vertices, std::vector<GLushort>* indices );

public:
    CylinderGeometry(double radiusTop = 1, double radiusBottom = 1, double height = 1, int radialSegments = 8, int heightSegments = 1, bool openEnded = false, double thetaStart = 0, double thetaLength = 2 * M_PI);
};


#endif //MODULETHREE_CYLINDERGEOMETRY_H
