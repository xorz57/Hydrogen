#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class VAO {
public:
    VAO();

    void Bind() const;
    void Unbind() const;
    void Delete() const;
    void SetFloat(GLuint index, GLsizei stride, void *pointer) const;
    void SetFloat2(GLuint index, GLsizei stride, void *pointer) const;
    void SetFloat3(GLuint index, GLsizei stride, void *pointer) const;

private:
    GLuint mID = 0;
};
