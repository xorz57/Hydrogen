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
            position += speed_multiplier * speed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position -= speed_multiplier * speed * static_cast<float>(dt) * mFront;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= speed_multiplier * speed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += speed_multiplier * speed * static_cast<float>(dt) * mRight;
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            position += speed_multiplier * speed * static_cast<float>(dt) * mUp;
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            position -= speed_multiplier * speed * static_cast<float>(dt) * mUp;
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

        yaw += sensitivity * static_cast<float>(cursor_x - window_hw);
        pitch += sensitivity * static_cast<float>(cursor_y - window_hh);

        Update();

        glfwSetCursorPos(window, window_hw, window_hh);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (!mFlag) {
            mFlag = true;
        }
    }
}

void Camera::Update() {
    yaw = glm::mod(yaw, +360.0f);
    pitch = glm::clamp(pitch, -89.0f, +89.0f);

    mFront = glm::normalize(glm::vec3(cos(glm::radians(yaw)) * cos(glm::radians(pitch)), sin(glm::radians(-pitch)), sin(glm::radians(yaw)) * cos(glm::radians(pitch))));
    mRight = glm::normalize(glm::cross(mFront, mUp));
}

glm::mat4 Camera::GetView() const {
    return glm::lookAt(position, position + mFront, mUp);
}

glm::mat4 Camera::GetProjection(float aspect) const {
    return glm::perspective(glm::radians(fov), aspect, near, far);
}
