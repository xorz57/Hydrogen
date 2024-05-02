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
    void SetVec3(const char *name, const glm::vec3 &value) const;
    void SetVec4(const char *name, const glm::vec4 &value) const;
    void SetMat3(const char *name, const glm::mat3 &matrix) const;
    void SetMat4(const char *name, const glm::mat4 &matrix) const;

private:
    GLint mProgram = 0;
};
