//
// Created by kkeiper1103 on 11/11/22.
//

#include "Camera.h"

#include <GLFW/glfw3.h>
#include <easylogging++.h>


std::map<GLFWwindow*, Camera*> sCameras;

Camera::Camera(const glm::vec3 &position) : position(position), target(0, 0, -1), direction() {
    glm::vec3 upAxis(0, 1, 0);

    right = glm::normalize(glm::cross(upAxis, direction));
    up = glm::cross(direction, right);

    update(0.016);
}

void Camera::update(double dt) {
    processKeyboardInput(dt);
    processMouseInput(dt);

    view = glm::lookAt(position, position + target, {0, 1, 0});
}

void Camera::attachTo(const Window &window) {
    _glfwWindow = window.getGlfwHandle();

    // set up the static instance so we can manipulate this camera from a glfw callback
    sCameras[_glfwWindow] = this;

    // capture the cursor
    // this change was because just simply capturing the cursor made it difficult to debug. there was no mouse even when
    // minimizing the window, so you couldn't inspect anything
    /*glfwSetWindowFocusCallback(_glfwWindow, [](GLFWwindow* window, int focused) {
        glfwSetInputMode(window, GLFW_CURSOR, focused == 1 ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    });*/

    // set up scroll handling
    glfwSetScrollCallback(_glfwWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
        sCameras[window]->processMouseScroll(window, xoffset, yoffset);
    });

    // set up mouse movement handling
    glfwSetCursorPosCallback(_glfwWindow, [](GLFWwindow* window, double xpos, double ypos) {

        // some flag variables that let us know if the mouse has been initialized previously
        static bool firstMouse = true;
        static float lastX, lastY;
        if(firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        // find out how far the mouse has moved, relatively speaking
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;

        // store the absolute positions so we can calculate the relative offsets next frame
        lastX = xpos;
        lastY = ypos;

        float sensitivity = .5f;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        // since glfw callbacks can't capture state, we're force to resort to ugly static maps to figure out which camera to manipulate
        sCameras[window]->rotation.y += xoffset;
        sCameras[window]->rotation.x -= yoffset;


        // Make sure that when pitch is out of bounds, the screen doesn't get flipped.
        if (sCameras[window]->rotation.x > 89.0f)
            sCameras[window]->rotation.x = 89.0f;

        if (sCameras[window]->rotation.x < -89.0f)
            sCameras[window]->rotation.x = -89.0f;
    });
}

void Camera::processKeyboardInput(double dt) {
    const float cameraSpeed = movementSpeed * dt;

    // prevent crashes from trying to find out if a key is pressed before the camera is attached to the window
    if(_glfwWindow == nullptr) return;


    if(glfwGetKey(_glfwWindow, GLFW_KEY_V) == GLFW_PRESS) {
        char buffer[255];
        sprintf(buffer, "Camera at (%.2f, %.2f, %.2f)", position.x, position.y, position.z);
        LOG(INFO) << buffer;
    }


    if (glfwGetKey(_glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
        position += cameraSpeed * target;
    if (glfwGetKey(_glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
        position -= cameraSpeed * target;
    if (glfwGetKey(_glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(target, {0, 1, 0})) * cameraSpeed;
    if (glfwGetKey(_glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(target, {0, 1, 0})) * cameraSpeed;


    if(glfwGetKey(_glfwWindow, GLFW_KEY_Q) == GLFW_PRESS)
        position.y -= 5.f * cameraSpeed;
    if(glfwGetKey(_glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
        position.y += 5.f * cameraSpeed;
}

void Camera::processMouseInput(double dt) {
    const float pitch = rotation.x,
        yaw = rotation.y;


    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


    target = glm::normalize(direction);
}

void Camera::processMouseScroll(GLFWwindow *window, double xoffset, double yoffset) {
    auto& fov = sCameras[window]->fieldOfView;

    fov -= (float) yoffset;

    if(fov < 1.f) fov = 1.f;
    if(fov > 45.f) fov = 45.f;

    // i hate these static map variables. they're SOOOO ugly
    sWindows[window]->rebuildProjectionMatrix();
}
