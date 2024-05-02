#pragma once

#include "Shader.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    void Focus(const Shader &shader, float fovy, float aspect, float near, float far) {
        const glm::mat4 view = glm::lookAt(mEye, mCenter, mUp);
        const glm::mat4 projection = glm::perspective(fovy, aspect, near, far);

        shader.SetFloat4x4("u_View", view);
        shader.SetFloat4x4("u_Projection", projection);
    }

private:
    glm::vec3 mEye{0.0f, 0.0f, 8.0f};
    glm::vec3 mCenter{0.0f, 0.0f, 0.0f};
    glm::vec3 mUp{0.0f, 1.0f, 0.0f};
    float speed = 0.5f;
};
