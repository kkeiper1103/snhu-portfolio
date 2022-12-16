//
// Created by kkeiper1103 on 11/6/22.
//

#include "Model.h"

#include "glm/ext/matrix_transform.hpp"
#include <easylogging++.h>

Model::Model(const std::shared_ptr<Mesh> &mesh, const glm::vec3 &position, const glm::vec3 &rotation, float scale) :
mesh(mesh), position(position), rotation(rotation), scale(scale) {

    computeModelMatrix();
}

Model::Model(const std::shared_ptr<Mesh> &mesh, const glm::vec3 &position, const glm::vec3 &rotation) : Model(mesh, position, rotation, 1) {}
Model::Model(const std::shared_ptr<Mesh> &mesh, const glm::vec3 &position) : Model(mesh, position, {}, 1) {}
Model::Model(const std::shared_ptr<Mesh> &mesh) : Model(mesh, {}, {}, 1) {}

void Model::update(double dt) {
    computeModelMatrix();

    mesh->update(dt);
}

void Model::render() {
    shader->use();
    shader->setMat4("model", model);

    // set the normal matrix by calculating it on the cpu
    // note from learnopengl.com said inversing matrices is costly, so do it on the cpu, not the gpu
    shader->setMat3("normalMatrix", glm::mat3(glm::transpose(glm::inverse(model))));

    mesh->render( shader );
}

void Model::setShader(const std::shared_ptr<Shader> &shader) {
    this->shader = shader;
}

void Model::computeModelMatrix() {
    // the static qualifier just means it doesn't get redeclared each time computeModelMatrix() is called. They're created once, then persisted across calls
    static glm::vec3 _position, _rotation;
    static float _scale;

    // if any of the cached properties don't match the object's properties, recompute the model matrix
    if(_position != position || _rotation != rotation || _scale != scale) {
        model = glm::mat4(1.f);
        model = glm::translate(model, position);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        model = glm::scale(model, glm::vec3(scale, scale, scale));

        // set the static flags to prevent re-computation unless the components change value
        _position = position;
        _rotation = rotation;
        _scale = scale;
    }
}

/**
 * for right now, we're just going to tell the window to render all models
 * eventually, this will take the camera's frustrum into account and see if the model's position is located within the camera's field of view
 *
 * @param camera
 * @return
 */
bool Model::isInView(const Camera &camera) {
    return true;
}
