//
// Created by kkeiper1103 on 11/6/22.
//

#ifndef MODULETWO_MODEL_H
#define MODULETWO_MODEL_H

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Shader.h"

// forward declaration because Camera references Window, Window references Model, etc
// include the real thing in Model.cpp
class Camera;

class Model {
protected:
    std::shared_ptr<Mesh> mesh = nullptr;
    std::shared_ptr<Shader> shader = nullptr;

    glm::mat4 model = glm::mat4(1.f);

    glm::vec3 position = glm::vec3(0, 0, 0);
    glm::vec3 rotation = glm::vec3(0, 0, 0);

    float scale = 1.0;


    void computeModelMatrix();

public:
    Model(const std::shared_ptr<Mesh>& mesh, const glm::vec3& position, const glm::vec3& rotation, float scale);
    Model(const std::shared_ptr<Mesh>& mesh, const glm::vec3& position, const glm::vec3& rotation);
    Model(const std::shared_ptr<Mesh>& mesh, const glm::vec3& position);
    explicit Model(const std::shared_ptr<Mesh>& mesh);

    void update(double dt);
    void render();


    // don't like this whole setShader business, but what else do I do?
    void setShader(const std::shared_ptr<Shader>& shader);


    // method to determine if the model is within the frustrum of the camera
    bool isInView(const Camera& camera);
};


#endif //MODULETWO_MODEL_H
