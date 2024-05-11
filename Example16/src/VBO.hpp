#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>

template<typename T>
class VBO {
public:
    explicit VBO(const std::vector<T> &vertices);

    void Bind() const;
    void Delete() const;

    static void Unbind();

private:
    GLuint mID = 0;
};

#include "VBO.inl"
