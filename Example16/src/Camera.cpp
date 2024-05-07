#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(CameraSettings &settings) : mSettings(settings) {
    mFront = glm::normalize(glm::vec3(cos(glm::radians(mSettings.yaw)) * cos(glm::radians(mSettings.pitch)), sin(glm::radians(-mSettings.pitch)), sin(glm::radians(mSettings.yaw)) * cos(glm::radians(mSettings.pitch))));
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
            mSettings.position += mSettings.speed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            mSettings.position -= mSettings.speed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            mSettings.position -= mSettings.speed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            mSettings.position += mSettings.speed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            mSettings.position += mSettings.speed * static_cast<float>(dt) * mUp;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            mSettings.position -= mSettings.speed * static_cast<float>(dt) * mUp;
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

        mSettings.yaw += mSettings.sensitivity * static_cast<float>(cursor_x - window_hw);
        mSettings.pitch += mSettings.sensitivity * static_cast<float>(cursor_y - window_hh);

        mSettings.pitch = glm::clamp(mSettings.pitch, -89.0f, +89.0f);

        mFront = glm::normalize(glm::vec3(cos(glm::radians(mSettings.yaw)) * cos(glm::radians(mSettings.pitch)), sin(glm::radians(-mSettings.pitch)), sin(glm::radians(mSettings.yaw)) * cos(glm::radians(mSettings.pitch))));
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
    mSettings.speed = speed;
}

glm::mat4 Camera::GetView() const {
    return glm::lookAt(mSettings.position, mSettings.position + mFront, mUp);
}

glm::mat4 Camera::GetProjection(float aspect) const {
    return glm::perspective(glm::radians(mSettings.fov), aspect, mSettings.near, mSettings.far);
}
