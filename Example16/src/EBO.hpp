#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>

template<typename T>
class EBO {
public:
    explicit EBO(const std::vector<T> &elements);

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint mID = 0;
};

#include "EBO.inl"
