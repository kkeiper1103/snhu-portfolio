//
// Created by kkeiper1103 on 11/6/22.
//

#ifndef MODULETWO_MESH_H
#define MODULETWO_MESH_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/normal.hpp>
#include <GL/glew.h>

#include "Vertex.h"

#include "Shader.h"
#include "Material.h"

class Mesh {

GLuint vaoId = 0;
GLuint vboId = 0;
GLuint eboId = 0;

std::vector<Vertex> vertices;
std::vector<GLushort> indices;
std::vector< std::shared_ptr<Material> > materials;

public:
    GLenum drawMode = GL_TRIANGLES; // this can be changed publicly to manage whether triangles, strips, fans, lines, etc are drawn

public:
    Mesh(std::vector<Vertex> vertices = {}, std::vector<GLushort> indices = {});
    ~Mesh();

    void update(double dt);
    void render( const std::shared_ptr<Shader>& shader = nullptr );

    void setData(std::vector<Vertex> vertices, std::vector<GLushort> indices);

    void addMaterial(const std::shared_ptr<Material>& material);


public:
    bool hasTextures = true;
    bool hasColors = true;


    // combines two meshes together
    Mesh* operator+( const Mesh& rhs ) {
        auto newMesh = new Mesh();

        newMesh->vertices = vertices;
        newMesh->indices = indices;

        newMesh->vertices.reserve( vertices.size() + rhs.vertices.size() );
        newMesh->indices.reserve( indices.size() + rhs.indices.size() );

        std::copy(rhs.vertices.begin(), rhs.vertices.end(), newMesh->vertices.end());
        std::copy(rhs.indices.begin(), rhs.indices.end(), newMesh->indices.end());

        return newMesh;
    }

    template <typename T>
    std::shared_ptr<T> operator+(const std::shared_ptr<T>& rhs) {
        std::vector<Vertex> vertices_ = vertices;
        vertices_.reserve(vertices.size() + rhs->vertices.size());

        std::vector<GLushort> indices_ = indices;
        indices_.reserve( indices.size() + rhs->indices.size() );


        std::copy(rhs->vertices.begin(), rhs->vertices.end(), vertices_.end());
        std::copy(rhs->indices.begin(), rhs->indices.end(), indices_.end());

        return std::make_shared<T>(vertices_, indices_);
    }
};


#endif //MODULETWO_MESH_H
