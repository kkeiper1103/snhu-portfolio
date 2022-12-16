//
// Created by kkeiper1103 on 11/12/22.
//

#ifndef PROJECTONE_CONTEXTOPTIONS_H
#define PROJECTONE_CONTEXTOPTIONS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct ContextOptions {
    int majorVersion = 4;
    int minorVersion = 4;

    int profileType = GLFW_OPENGL_CORE_PROFILE;

    int samples = 4;

    bool debugMode = false;
};

#endif //PROJECTONE_CONTEXTOPTIONS_H
