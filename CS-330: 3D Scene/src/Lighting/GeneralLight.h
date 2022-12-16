//
// Created by kkeiper1103 on 11/14/22.
//

#ifndef PROJECTONE_GENERALLIGHT_H
#define PROJECTONE_GENERALLIGHT_H


#include "LightSource.h"

class GeneralLight : public LightSource {
public:
    glm::vec3 direction {0, 0, 0};

    glm::vec4 ambient {1, 1, 1, 0.05}; // 5% white light
    glm::vec4 diffuse {1, 1, 1, 0.8}; // 80% white light
    glm::vec4 specular {1, 1, 1, 1}; // 100% white light

    float constant = 1.f;
    float linear = .09f;
    float quadratic = .032f;

    float cutOff = 0.91f;
    float outerCutOff = 0.82f;
    float phi = 0.91f;
    float theta = 0.97f;

public:
    explicit GeneralLight( const glm::vec3& position );

    void apply(const std::shared_ptr<Shader> &shader, int uniformIndex) override;
};


#endif //PROJECTONE_GENERALLIGHT_H
