#pragma once

#include <glm/glm.hpp>

struct CameraSettings {
    glm::vec3 position{+0.0f, +0.0f, +0.0f};
    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;
    float pitch = 0.0f;
    float yaw = 0.0f;
    float sensitivity = 0.1f;
    float speed = 2.0f;
};
