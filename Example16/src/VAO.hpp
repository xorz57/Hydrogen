#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>

class VAO {
public:
    VAO();

    void Bind() const;
    void Delete() const;

    static std::shared_ptr<VAO> Create();
    static void Unbind();
    static void SetFloat(GLuint index, GLsizei stride, const void *pointer);
    static void SetFloat2(GLuint index, GLsizei stride, const void *pointer);
    static void SetFloat3(GLuint index, GLsizei stride, const void *pointer);

private:
    GLuint mID = 0;
};
