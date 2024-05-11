#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    Update();
}

void Camera::ProcessInput(float window_w, float window_h, double dt) {
    auto window = glfwGetCurrentContext();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        float speed_multiplier;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            speed_multiplier = 2.0f;
        } else {
            speed_multiplier = 1.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            mPosition += speed_multiplier * mSpeed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            mPosition -= speed_multiplier * mSpeed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            mPosition -= speed_multiplier * mSpeed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            mPosition += speed_multiplier * mSpeed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            mPosition += speed_multiplier * mSpeed * static_cast<float>(dt) * mUp;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            mPosition -= speed_multiplier * mSpeed * static_cast<float>(dt) * mUp;
        }

        const double window_hw = 0.5f * window_w;
        const double window_hh = 0.5f * window_h;

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (mFlag) {
            glfwSetCursorPos(window, window_hw, window_hh);
            mFlag = false;
        }

        double cursor_x;
        double cursor_y;
        glfwGetCursorPos(window, &cursor_x, &cursor_y);

        mYaw += mSensitivity * static_cast<float>(cursor_x - window_hw);
        mPitch += mSensitivity * static_cast<float>(cursor_y - window_hh);

        glfwSetCursorPos(window, window_hw, window_hh);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (!mFlag) {
            mFlag = true;
        }
    }
}

void Camera::Update() {
    mYaw = glm::mod(mYaw, +360.0f);
    mPitch = glm::clamp(mPitch, -89.0f, +89.0f);

    mFront = glm::normalize(glm::vec3(cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)), sin(glm::radians(-mPitch)), sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))));
    mRight = glm::normalize(glm::cross(mFront, mUp));
}

glm::mat4 Camera::GetView() const {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::GetProjection(float aspect) const {
    return glm::perspective(glm::radians(mFOV), aspect, mNear, mFar);
}

void Camera::SetPosition(const glm::vec3 &position) {
    mPosition = position;
}

void Camera::SetFOV(float fov) {
    mFOV = fov;
}

void Camera::SetNear(float near) {
    mNear = near;
}

void Camera::SetFar(float far) {
    mFar = far;
}

void Camera::SetPitch(float pitch) {
    mPitch = pitch;
}

void Camera::SetYaw(float yaw) {
    mYaw = yaw;
}

void Camera::SetSensitivity(float sensitivity) {
    mSensitivity = sensitivity;
}

void Camera::SetSpeed(float speed) {
    mSpeed = speed;
}

glm::vec3 Camera::GetPosition() const {
    return mPosition;
}

float Camera::GetFOV() const {
    return mFOV;
}

float Camera::GetNear() const {
    return mNear;
}

float Camera::GetFar() const {
    return mFar;
}

float Camera::GetPitch() const {
    return mPitch;
}

float Camera::GetYaw() const {
    return mYaw;
}

float Camera::GetSensitivity() const {
    return mSensitivity;
}

float Camera::GetSpeed() const {
    return mSpeed;
}