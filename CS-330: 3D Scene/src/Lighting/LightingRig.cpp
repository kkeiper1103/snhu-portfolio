//
// Created by kkeiper1103 on 11/13/22.
//

#include "LightingRig.h"

#include <easylogging++.h>

void LightingRig::addLight(const std::shared_ptr<GeneralLight> &light) {
    generalLights.push_back(light);
}

void LightingRig::applyTo(const std::shared_ptr<Shader> &shader) {
    for(auto i=0; i < generalLights.size(); i++) {
        generalLights[i]->apply(shader, i);
    }
}
