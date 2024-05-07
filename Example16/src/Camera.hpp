#pragma once

#include "CameraSettings.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera {
public:
    Camera(CameraSettings &settings);

    void Update(float window_w, float window_h, double dt);
    glm::mat4 GetView() const;
    glm::mat4 GetProjection(float aspect) const;

private:
    glm::vec3 mFront{+0.0f, +0.0f, -1.0f};
    glm::vec3 mUp{+0.0f, +1.0f, +0.0f};
    glm::vec3 mRight = glm::normalize(glm::cross(mFront, mUp));
    CameraSettings &mSettings;
    bool mFlag = true;
};
