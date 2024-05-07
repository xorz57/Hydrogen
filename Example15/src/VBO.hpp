#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>

template<typename T>
class VBO {
public:
    VBO(const std::vector<T> &vertices);

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint mID = 0;
};

#include "VBO.inl"
