//
// Created by kkeiper1103 on 11/7/22.
//

#ifndef MODULETWO_MATERIAL_H
#define MODULETWO_MATERIAL_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class Material {
private:
    GLuint id;

    int width = 0, height = 0;
    unsigned char* data = nullptr;

public:
    GLint internalFormat = GL_RGBA;
    GLenum format = GL_RGBA;
    GLenum type = GL_UNSIGNED_BYTE;

    int level = 0;
    int border = 0;

    // fields for material properties
    float shininess = 1.f;
    float metallic = 0.0f;
    float roughness = 0.2f;
    float anisotropic = 0.f;
    float opticalDensity = 1.f;
    float dissolveFactor = 1.f;
    int illuminationMethod = 2;

    glm::vec3 ambient; // Ka
    glm::vec3 diffuse; // Kd
    glm::vec3 specular;// Ks

public:
    Material(int width, int height, unsigned char* data);
    explicit Material(const std::string& filename);
    ~Material();

    void apply(int slotOffset = 0) const;

    [[nodiscard]] unsigned char* GetData() const { return data; }


    void upload();
};


#endif //MODULETWO_MATERIAL_H
