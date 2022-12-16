//
// Created by kkeiper1103 on 11/6/22.
//

#include "Shader.h"

#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <fstream>
#include <map>

#include <glm/gtc/type_ptr.hpp>

std::map<GLuint, const char*> types = {
    {GL_VERTEX_SHADER, "Vertex Shader"},
    {GL_FRAGMENT_SHADER, "Fragment Shader"},
    {GL_GEOMETRY_SHADER, "Geometry Shader"},
};

Shader::Shader(const char *vs, const char *fs, const char *gs) {
    programId = glCreateProgram();

    if(!vs) throw std::runtime_error("Can't Create Shader without VertexShaderSource!");
    if(!fs) throw std::runtime_error("Can't Create Shader without FragmentShaderSource!");

    shaders.push_back(createShaderFragment(GL_VERTEX_SHADER, vs));
    shaders.push_back(createShaderFragment(GL_FRAGMENT_SHADER, fs));

    if(gs) shaders.push_back(createShaderFragment(GL_GEOMETRY_SHADER, gs));

    for(auto& id: shaders)
        glAttachShader(programId, id);

    glLinkProgram(programId);

    //
    int linked;
    glGetProgramiv(programId, GL_LINK_STATUS, &linked);
    if(!linked) {
        char buffer[255];
        glGetProgramInfoLog(programId, sizeof(buffer), nullptr, buffer);

        std::cerr << "Error Linking Program: " << std::endl << buffer << std::endl;
    }
}

// delegate constructors
Shader::Shader(const std::string &vs, const std::string &fs) : Shader(vs.c_str(), fs.c_str()){}
Shader::Shader(const std::string &vs, const std::string &fs, const std::string &gs) : Shader(vs.c_str(), fs.c_str(), gs.c_str()) {}

Shader::~Shader() {

    // can't use LOG(INFO) here because the logger is gone when this is called. One of the weaknesses of easylogginpp
    std::cout << "[debug] deleting " << shaders.size() << " shader fragments\n";

    for(auto& shaderId: shaders)
        glDeleteShader(shaderId);

    glDeleteProgram(programId);
}

GLuint Shader::createShaderFragment(GLuint type, const char *source) {
    GLuint id = glCreateShader(type);

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // error checking
    int compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if(!compiled) {
        char buffer[255];
        glGetShaderInfoLog(id, sizeof(buffer), nullptr, buffer);

        std::cerr << "Error Compiling " << types[type] << ": " << std::endl << buffer << std::endl;
    }

    return id;
}

std::shared_ptr<Shader> Shader::FromFiles(const std::string &vsFile, const std::string &fsFile) {
    using namespace std;

    // @todo reduce wetness of code. Lots of repeats here

    // read vert source
    stringstream os(stringstream::out);
    os << ifstream(vsFile).rdbuf();
    string vsSource(os.str());

    // read frag source
    os = stringstream(stringstream::out);
    os << ifstream(fsFile).rdbuf();
    string fsSource(os.str());

    return std::make_shared<Shader>(vsSource, fsSource);
}

std::shared_ptr<Shader> Shader::FromFiles(const std::string &vsFile, const std::string &fsFile, const std::string &gsFile) {
    using namespace std;

    // @todo reduce wetness of code. Lots of repeats here

    // read vert source
    stringstream os(stringstream::out);
    os << ifstream(vsFile).rdbuf();
    string vsSource(os.str());

    // read frag source
    os = stringstream(stringstream::out);
    os << ifstream(fsFile).rdbuf();
    string fsSource(os.str());

    // read geom source
    os = stringstream(stringstream::out);
    os << ifstream(fsFile).rdbuf();
    string gsSource(os.str());

    return std::make_shared<Shader>(vsSource, fsSource, gsSource);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const {
    use();
    glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, false, glm::value_ptr(value));
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    use();
    glUniform2f(glGetUniformLocation(programId, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    use();
    glUniform3f(glGetUniformLocation(programId, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    use();
    glUniform4f(glGetUniformLocation(programId, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setInt(const std::string &name, const int &value) const {
    use();
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float &value) const {
    use();
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

GLuint Shader::getUniformLocation(const std::string &name) {
    return glGetUniformLocation(programId, name.c_str());
}

void Shader::setMat3(const std::string &name, const glm::mat3 &value) const {
    use();
    glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, false, glm::value_ptr(value));
}
