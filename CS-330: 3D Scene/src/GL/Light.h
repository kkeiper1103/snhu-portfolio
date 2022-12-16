//
// Created by kkeiper1103 on 12/2/22.
//

#ifndef MODULESIX_LIGHT_H
#define MODULESIX_LIGHT_H

#include <glm/glm.hpp>

struct Light {
    // taken from table on https://learnopengl.com/Lighting/Light-casters
    float constant{1.0};
    float linear{.22};
    float quadratic{.20};

    glm::vec4 ambient{0, 0, 0, 0};
    glm::vec4 diffuse{0, 0, 0, 0};
    glm::vec4 specular{0, 0, 0, 0};

    glm::vec3 position{0, 10, 0};

    // normalized direction
    glm::vec3 direction{0, 0, 0};
};

#endif //MODULESIX_LIGHT_H
