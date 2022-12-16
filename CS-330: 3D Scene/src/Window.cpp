//
// Created by kkeiper1103 on 11/10/22.
//

#include "Window.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "GL/Model.h"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.h"

#include <easylogging++.h>

// YUCK
std::map<GLFWwindow*, Window*> sWindows;

// debug callback, in case the user has requested a debug version of opengl
void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    char buffer[255];
    sprintf(buffer, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s", ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message);

    if(type == GL_DEBUG_TYPE_ERROR)
        LOG(ERROR) << buffer;
    else
        LOG(DEBUG) << buffer;
}

Window::Window(const std::string &title, int width, int height, ContextOptions glContextOptions) {
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_SAMPLES, glContextOptions.samples);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glContextOptions.majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glContextOptions.minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, glContextOptions.profileType);

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    // ... I HATE THIS
    // statically add the "this" object to the dictionary of window handles
    sWindows[handle] = this;

    init();

    // call the resize handler manually to set the projection matrix
    resize(handle, width, height);

    // enable debugging if requested
    if(glContextOptions.debugMode) {
        LOG(INFO) << "Enabling GL Debug Mode";

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, nullptr);
    }
}

Window::~Window() {
    // remove the handle from the map
    sWindows[handle] = nullptr;

    glfwDestroyWindow(handle);
}

bool Window::open() const {
    return !glfwWindowShouldClose(handle);
}

void Window::clear() {
    glClearDepth(1.f);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap() {
    glfwSwapBuffers(handle);

    // clear the rendering queue
    renderQueue.clear();
}

void Window::init() {
    glfwMakeContextCurrent(handle); // associate gl context with the current thread?

    glfwSetFramebufferSizeCallback(handle, &Window::resize);

    // quit if someone presses escape
    glfwSetKeyCallback(handle, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, 1);

        // change the projection matrix mode
        if(key == GLFW_KEY_P && action == GLFW_PRESS) {

            if(sWindows[window]->projectionMode == ProjectionMode::PERSPECTIVE) {
                sWindows[window]->projectionMode = ProjectionMode::ORTHOGRAPHIC;
            }

            else if(sWindows[window]->projectionMode == ProjectionMode::ORTHOGRAPHIC) {
                sWindows[window]->projectionMode = ProjectionMode::PERSPECTIVE;
            }

            LOG(INFO) << "Switching Projection Mode to " << ((sWindows[window]->projectionMode == ProjectionMode::PERSPECTIVE) ?
                "Perspective" : "Orthographic");

            // self-explanatory
            sWindows[window]->rebuildProjectionMatrix();
        }
    });

    // make sure glew loads
    assert(glewInit() == GLEW_OK && "Unable to Initialize GLEW");

    // since we're doing 3d, not 2d, enable the depth test so we don't draw incorrectly ordered z-objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    LOG(INFO) << "Running Application with GL Driver: " << glGetString(GL_VERSION);
}

void Window::resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);

    // lookup the Window* object and set the projectionMatrix again when the viewport is resized
    // this is like looking up a record in a relational database (select * from windows where windows.handle like :handleId)
    sWindows[window]->rebuildProjectionMatrix();

    LOG(INFO) << "Resizing Window To " << width << "x" << height;
}

void Window::queueForRendering(const std::shared_ptr<Model> &model) {
    renderQueue.push_back(model);
}

void Window::renderModels() {
    // we render only what has been queued for rendering, so we don't send unnecessary data to the gpu
    for(auto& model: renderQueue) {
        model->render();
    }
}

void Window::updateModels(double dt) {
    // we use the entire model collection, not a subset, since we want to simulate the entire scene
    for(auto& model: modelCollection) {
        model->update(dt);
    }
}

void Window::rebuildProjectionMatrix() {
    // get window width and height
    int width, height;
    glfwGetWindowSize(handle, &width, &height);

    float fov = (sCameras[handle] != nullptr) ? sCameras[handle]->GetFieldOfView() : 45.f;
    float zoom = glm::radians( fov );

    // rebuild the matrix now
    sWindows[handle]->projectionMatrix = (sWindows[handle]->projectionMode == ProjectionMode::PERSPECTIVE) ?
         glm::perspective(zoom, (float) width / (float) height, .1f, 100.f) :
         glm::ortho( -10.f, 10.f, -10.f, 10.f, .1f, 100.0f );
}
