//
// Created by kkeiper1103 on 11/13/22.
//

#ifndef PROJECTONE_LIGHTSOURCE_H
#define PROJECTONE_LIGHTSOURCE_H

#include <glm/glm.hpp>

#include "../GL/Shader.h"

class LightSource {
protected:
    glm::vec4 color = glm::vec4 (1, 1, 1, 1);

    // not sure yet
    glm::vec3 position;
    glm::mat4 model;

    // still not sure
    std::shared_ptr<Shader> shader;

public:
    explicit LightSource(const glm::vec3& position, const glm::vec4& color = {1, 1, 1, 1});
    explicit LightSource(const glm::vec3& position, const glm::vec3& color = {1, 1, 1});
    virtual ~LightSource();



    virtual void apply(const std::shared_ptr<Shader>& shader, int uniformIndex) = 0;
};

#endif //PROJECTONE_LIGHTSOURCE_H
