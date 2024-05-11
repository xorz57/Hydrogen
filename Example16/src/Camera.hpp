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

    void SetPosition(const glm::vec3 &position);
    void SetFOV(float fov);
    void SetNear(float near);
    void SetFar(float far);
    void SetPitch(float pitch);
    void SetYaw(float yaw);
    void SetSensitivity(float sensitivity);
    void SetSpeed(float speed);

    [[nodiscard]] glm::vec3 GetPosition() const;
    [[nodiscard]] float GetFOV() const;
    [[nodiscard]] float GetNear() const;
    [[nodiscard]] float GetFar() const;
    [[nodiscard]] float GetPitch() const;
    [[nodiscard]] float GetYaw() const;
    [[nodiscard]] float GetSensitivity() const;
    [[nodiscard]] float GetSpeed() const;

    [[nodiscard]] glm::mat4 GetView() const;
    [[nodiscard]] glm::mat4 GetProjection(float aspect) const;

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
