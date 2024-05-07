#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 &position) : mPosition(position) {
    mFront = glm::normalize(glm::vec3(cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)), sin(glm::radians(-mPitch)), sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))));
    mRight = glm::normalize(glm::cross(mFront, mUp));
}

void Camera::Move(float window_w, float window_h, double dt) {
    auto window = glfwGetCurrentContext();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            SetSpeed(4.0f);
        } else {
            SetSpeed(2.0f);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            mPosition += mSpeed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            mPosition -= mSpeed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            mPosition -= mSpeed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            mPosition += mSpeed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            mPosition += mSpeed * static_cast<float>(dt) * mUp;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            mPosition -= mSpeed * static_cast<float>(dt) * mUp;
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

        mPitch = glm::clamp(mPitch, -89.0f, +89.0f);

        mFront = glm::normalize(glm::vec3(cos(glm::radians(mYaw)) * cos(glm::radians(mPitch)), sin(glm::radians(-mPitch)), sin(glm::radians(mYaw)) * cos(glm::radians(mPitch))));
        mRight = glm::normalize(glm::cross(mFront, mUp));

        glfwSetCursorPos(window, window_hw, window_hh);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (!mFlag) {
            mFlag = true;
        }
    }
}

void Camera::SetSpeed(float speed) {
    mSpeed = speed;
}

glm::mat4 Camera::GetView() const {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::GetProjection(float aspect) const {
    return glm::perspective(mFOV, aspect, mNear, mFar);
}
