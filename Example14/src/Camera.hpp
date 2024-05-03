#pragma once

#include "Shader.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    void SetViewMatrix(const Shader &shader, const char *name) const;
    void SetProjectionMatrix(const Shader &shader, const char *name, float fovy, float aspect, float near, float far) const;

private:
    glm::vec3 mEye{0.0f, 0.0f, 8.0f};
    glm::vec3 mCenter{0.0f, 0.0f, 0.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
};
