#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

class Camera {
public:
    Camera();

    void Move(float window_w, float window_h, double dt);
    void SetSpeed(float speed);
    glm::mat4 GetView() const;
    glm::mat4 GetProjection(float aspect) const;

private:
    glm::vec3 mPosition{+0.0f, +8.0f, +8.0f};
    glm::vec3 mFront{+0.0f, +0.0f, -1.0f};
    glm::vec3 mUp{+0.0f, +1.0f, +0.0f};
    float mFOV = glm::radians(45.0f);
    float mNear = 0.1f;
    float mFar = 100.0f;
    float mPitch = 45.0f;
    float mYaw = -90.0f;
    float mSensitivity = 0.1f;
    float mSpeed = 2.0f;
    bool mFlag = true;
};
