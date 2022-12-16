//
// Created by kkeiper1103 on 11/10/22.
//

#ifndef MODULETHREE_WINDOW_H
#define MODULETHREE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "ContextOptions.h"

// forward declaration to prevent circular dependencies
class Model;
typedef std::vector<std::shared_ptr<Model>> ModelCollection;

enum class ProjectionMode {
    PERSPECTIVE = 0,
    ORTHOGRAPHIC
};

class Window {
GLFWwindow* handle = nullptr;
glm::vec4 clearColor = {0.1, 0.1, 0.1, 1};

ProjectionMode projectionMode = ProjectionMode::PERSPECTIVE;
glm::mat4 projectionMatrix = glm::mat4(1.f);

void init();
static void resize(GLFWwindow* window, int width, int height);

public:
    ModelCollection modelCollection; // stores *all* models. Call update on this
    ModelCollection renderQueue; // stores *only* models within the frustrum, to limit draw calls. Call render on this
    void queueForRendering(const std::shared_ptr<Model>& model);

public:
    Window(const std::string& title, int width, int height, ContextOptions glContextOptions = {});
    ~Window();


    [[nodiscard]] bool open() const;
    void clear();
    void updateModels(double dt);
    void renderModels();
    void swap();

    // nodiscard means that the compiler should not optimize away the function call
    // a bad compiler might just put the projectionMatrix raw values into the compiled .o file, meaning the projectionMatrix
    // would never get updated after the framebufferresize event
    [[nodiscard]] inline const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }


    // used by the camera to handle events on the window
    [[nodiscard]] GLFWwindow* getGlfwHandle() const { return handle; }

    void rebuildProjectionMatrix();
};

// YUCK
// glfw uses c-style callbacks for resize, so I can't access any member properties of the userland Window class
// to circumvent this, I've got a static map that is keyed by GLFWwindow* handle. This allows me to access
// the custom properties on Window* when all I have is a GLFWwindow* handle in the callback function
extern std::map<GLFWwindow*, Window*> sWindows;

#endif //MODULETHREE_WINDOW_H
