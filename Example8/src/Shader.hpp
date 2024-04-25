#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Shader {
public:
    Shader(const char *vShaderSource, const char *fShaderSource);
    ~Shader();

    void use();

private:
    GLint mProgram = 0;
};