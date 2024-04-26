#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Shader {
public:
    Shader(const GLchar *vShaderSource, const GLchar *fShaderSource);
    ~Shader();

    static Shader loadFromFile(const char *vShaderPath, const char *fShaderPath);
    void use() const;

private:
    GLint mProgram = 0;
};