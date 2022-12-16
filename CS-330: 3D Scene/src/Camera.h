//
// Created by kkeiper1103 on 11/11/22.
//

#ifndef MODULETHREE_CAMERA_H
#define MODULETHREE_CAMERA_H

#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"

class Camera {
protected:
    glm::vec3 position, target, direction, up, right;
    glm::vec3 rotation {0, 270, 0};

    float fieldOfView = 45.f;
    float movementSpeed = 2.5f;

    GLFWwindow* _glfwWindow = nullptr;
    glm::mat4 view = glm::mat4(1.f);

public:
    [[nodiscard]] glm::vec3 GetPosition() const { return position; }
    [[nodiscard]] glm::mat4 GetView() const { return view; }
    [[nodiscard]] float GetFieldOfView() const { return fieldOfView; }

public:
    explicit Camera(const glm::vec3& position);


    void update(double dt);

    void attachTo(const Window &window);


    virtual void processKeyboardInput(double dt);
    virtual void processMouseInput(double dt);
    virtual void processMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
};


// I really hate glfw callbacks. SDL rules
extern std::map<GLFWwindow*, Camera*> sCameras;

#endif //MODULETHREE_CAMERA_H
