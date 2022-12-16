//
// Created by kkeiper1103 on 11/7/22.
//

#include "Material.h"

// since the Material class is the one that needs the pixels from a .png/.jpg, etc
// we'll insert the stb loader here
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Material::Material(int width, int height, unsigned char *data) : width(width), height(height), data(data) {
    glGenTextures(1, &id);

    upload();
}

Material::~Material() {
    glDeleteTextures(1, &id);
}


void Material::apply(int slotOffset) const {
    glActiveTexture(GL_TEXTURE0 + slotOffset);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Material::upload() {
    /**
     * upload the texture to the gpu
     */
    glBindTexture(GL_TEXTURE_2D, id);
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // if a parameter is > 1.f, just repeat the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // same
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // this moves the pixels onto the gpu using the parameters defined
        glTexImage2D(GL_TEXTURE_2D, level, internalFormat, width, height, border, format, type, data);

        // without this call, textures will be blank because gl is expecting to find mipmaps
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

Material::Material(const std::string &filename) {
    glGenTextures(1, &id);

    int c;
    data = stbi_load(filename.c_str(), &width, &height, &c, STBI_default);
    if(data) {
        format = (c == 3) ? GL_RGB : GL_RGBA;

        upload();

        stbi_image_free(data);
    }
}
