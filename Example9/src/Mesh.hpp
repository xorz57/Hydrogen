#pragma once

#include "Vertex.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLint> &elements);
    ~Mesh();

    void draw();

    std::vector<Vertex> vertices;
    std::vector<GLint> elements;

private:
    GLuint mVAO = 0;
    GLuint mVBO = 0;
    GLuint mEBO = 0;
};