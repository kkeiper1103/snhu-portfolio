//
// Created by kkeiper1103 on 11/14/22.
//

#include "GeneralLight.h"

GeneralLight::GeneralLight(const glm::vec3 &position) : LightSource(position, {1, 1, 1, 1}) {}

void GeneralLight::apply(const std::shared_ptr<Shader> &shader, int uniformIndex) {
    char base[255];
    sprintf(base, "lights[%d]", uniformIndex);

    shader->setInt(std::string(base) + ".isActive", 1);

    shader->setVec3(std::string(base) + ".position", position);
    shader->setVec3(std::string(base) + ".direction", direction);
    shader->setVec4(std::string(base) + ".ambientColor", ambient);
    shader->setVec4(std::string(base) + ".diffuseColor", diffuse);
    shader->setVec4(std::string(base) + ".specularColor", specular);

    shader->setFloat(std::string(base) + ".constantFactor", constant);
    shader->setFloat(std::string(base) + ".linearFactor", linear);
    shader->setFloat(std::string(base) + ".quadraticFactor", quadratic);

    shader->setFloat(std::string(base) + ".cutOff", cutOff);
    shader->setFloat(std::string(base) + ".outerCutOff", outerCutOff);
    shader->setFloat(std::string(base) + ".phi", phi);
    shader->setFloat(std::string(base) + ".theta", theta);
}

