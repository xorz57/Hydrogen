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
    [[nodiscard]] glm::mat4 GetView() const;
    [[nodiscard]] glm::mat4 GetProjection(float aspect) const;
    [[nodiscard]] glm::vec3 &GetPosition();
    [[nodiscard]] float &GetFOV();
    [[nodiscard]] float &GetNear();
    [[nodiscard]] float &GetFar();
    [[nodiscard]] float &GetPitch();
    [[nodiscard]] float &GetYaw();
    [[nodiscard]] float &GetSensitivity();
    [[nodiscard]] float &GetSpeed();

private:
    glm::vec3 mFront{+0.0f, +0.0f, -1.0f};
    glm::vec3 mUp{+0.0f, +1.0f, +0.0f};
    glm::vec3 mRight = glm::normalize(glm::cross(mFront, mUp));
    glm::vec3 mPosition{+0.0f, +0.0f, +0.0f};
    float mFOV = 45.0f;
    float mNear = 0.1f;
    float mFar = 100.0f;
    float mPitch = 0.0f;
    float mYaw = 0.0f;
    float mSensitivity = 0.1f;
    float mSpeed = 1.0f;
    bool mFlag = true;
};
