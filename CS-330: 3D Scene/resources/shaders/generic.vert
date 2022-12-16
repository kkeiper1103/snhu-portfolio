#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in vec3 normal;

// this is the combined projection*view matrix
// we combine it on the cpu for performance reasons
uniform mat4 pv;
uniform mat4 model;

out vec4 oColor;
out vec2 oTextureCoord;
out vec3 oNormal;
out vec3 oFragPosition;

void main() {
    gl_Position = pv * model * vec4(position, 1);

    oColor = color;
    oTextureCoord = textureCoord;
    oNormal = mat3(transpose(inverse(model))) * normal;
    oFragPosition = vec3(model * vec4(position, 1));
}
