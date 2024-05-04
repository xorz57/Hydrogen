#pragma once

#include "Vertex.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>

class VBO {
public:
    VBO(const std::vector<Vertex> &vertices);

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint mID = 0;
};
