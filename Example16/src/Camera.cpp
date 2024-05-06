#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(-mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(front);
}

void Camera::Move(float window_w, float window_h, double dt) {
    auto window = glfwGetCurrentContext();

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        mSpeed = 4.0f;
    } else {
        mSpeed = 2.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        mPosition += mSpeed * static_cast<float>(dt) * mFront;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        mPosition -= mSpeed * static_cast<float>(dt) * mFront;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        mPosition += mSpeed * static_cast<float>(dt) * mUp;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        mPosition -= mSpeed * static_cast<float>(dt) * mUp;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        mPosition -= mSpeed * static_cast<float>(dt) * glm::normalize(glm::cross(mFront, mUp));
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        mPosition += mSpeed * static_cast<float>(dt) * glm::normalize(glm::cross(mFront, mUp));
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
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

        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(-mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

        mFront = glm::normalize(front);

        glfwSetCursorPos(window, window_hw, window_hh);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (!mFlag) {
            mFlag = true;
        }
    }
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(mPosition, mPosition + mFront, mUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspect) const {
    const float factor = 2.0f;
    return glm::ortho(-factor, +factor, -factor / aspect, +factor / aspect, 0.1f, 100.0f);
}
