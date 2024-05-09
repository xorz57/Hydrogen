#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera {
public:
    Camera();

    void ProcessInput(float window_w, float window_h, double dt);
    void Update();
    glm::mat4 GetView() const;
    glm::mat4 GetProjection(float aspect) const;

    glm::vec3 position{+0.0f, +0.0f, +0.0f};
    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float sensitivity = 0.1f;
    float speed = 1.0f;

private:
    glm::vec3 mFront{+0.0f, +0.0f, -1.0f};
    glm::vec3 mUp{+0.0f, +1.0f, +0.0f};
    glm::vec3 mRight = glm::normalize(glm::cross(mFront, mUp));
    bool mFlag = true;
};
