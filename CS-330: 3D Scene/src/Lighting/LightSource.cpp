//
// Created by kkeiper1103 on 11/13/22.
//

#include "LightSource.h"

LightSource::LightSource(const glm::vec3 &position, const glm::vec4 &color) : position(position), color(color) {

}

LightSource::LightSource(const glm::vec3 &position, const glm::vec3 &color) :
    LightSource(position, glm::vec4(color.r, color.g, color.b, 1)) {} // delegate constructor

LightSource::~LightSource() {

}
