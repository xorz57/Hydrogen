#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
public:
    Shader(const GLchar *vShaderSource, const GLchar *fShaderSource);
    ~Shader();

    static Shader loadFromFile(const char *vShaderPath, const char *fShaderPath);
    void setVec3(const char *name, const glm::vec3 &value) const;
    void setVec4(const char *name, const glm::vec4 &value) const;
    void setMat3(const char *name, const glm::mat3 &matrix) const;
    void setMat4(const char *name, const glm::mat4 &matrix) const;
    void use() const;

private:
    GLint mProgram = 0;
};
