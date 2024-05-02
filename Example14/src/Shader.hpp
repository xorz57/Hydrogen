#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
public:
    Shader(const GLchar *vShaderSource, const GLchar *fShaderSource);

    static Shader LoadFromFile(const char *vShaderPath, const char *fShaderPath);

    void Use() const;
    void Delete() const;
    void SetFloat3(const char *name, const glm::vec3 &v) const;
    void SetFloat4(const char *name, const glm::vec4 &v) const;
    void SetFloat3x3(const char *name, const glm::mat3 &m) const;
    void SetFloat4x4(const char *name, const glm::mat4 &m) const;

private:
    GLint mProgram = 0;
};
