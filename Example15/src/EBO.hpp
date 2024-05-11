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
    void Delete() const;

    static void Unbind();

private:
    GLuint mID = 0;
};

#include "EBO.inl"
