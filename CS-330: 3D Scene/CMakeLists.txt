cmake_minimum_required(VERSION 3.20)

# change THIS
project(MilestoneProject)

add_subdirectory(vendor/glfw-3.3.8)
add_subdirectory(vendor/glew-2.1.0/build/cmake)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES

        # framework files
        src/Camera.cpp
        src/Window.cpp

        src/GL/Material.cpp
        src/GL/Mesh.cpp
        src/GL/Model.cpp
        src/GL/Shader.cpp

        src/Geometry/CubeGeometry.cpp
        src/Geometry/CylinderGeometry.cpp
        src/Geometry/PyramidGeometry.cpp
        src/Geometry/SphereGeometry.cpp

        src/Lighting/LightSource.cpp
        src/Lighting/LightingRig.cpp
        src/Lighting/GeneralLight.cpp

        src/Utils/Timer.cpp

        # make sure easylogging is compiled in
        vendor/easyloggingpp-9.97.0/src/easylogging++.cc

        #add tinyobj support
        vendor/tinyobjloader/tiny_obj_loader.cc
)

add_executable(${PROJECT_NAME} milestone.cpp ${SOURCES})


# GL/glu.h isn't used in modern opengl, so we're telling GLEW to ingnore it when building
add_compile_definitions(GLEW_NO_GLU)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS} vendor/glew-2.1.0/include vendor/glm-0.9.9.8 vendor vendor/easyloggingpp-9.97.0/src)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glew glfw)
