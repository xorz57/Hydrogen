#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class VAO {
public:
    VAO();

    static void Unbind();
    static void SetFloat(GLuint index, GLsizei stride, void *pointer);
    static void SetFloat2(GLuint index, GLsizei stride, void *pointer);
    static void SetFloat3(GLuint index, GLsizei stride, void *pointer);

    void Bind() const;
    void Delete() const;

private:
    GLuint mID = 0;
};
