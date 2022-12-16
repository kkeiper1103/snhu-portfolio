//
// Created by kkeiper1103 on 11/13/22.
//

#ifndef PROJECTONE_LIGHTINGRIG_H
#define PROJECTONE_LIGHTINGRIG_H

#include <vector>

#include "GeneralLight.h"

class LightingRig {
    std::vector< std::shared_ptr<GeneralLight> > generalLights;

public:
    void addLight( const std::shared_ptr<GeneralLight>& light );

    void applyTo( const std::shared_ptr<Shader>& shader );
};


#endif //PROJECTONE_LIGHTINGRIG_H
