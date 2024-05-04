#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(-mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

    mFront = glm::normalize(front);
}

void Camera::Move(float display_w, float display_h, double dt) {
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
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (mFlag) {
            glfwSetCursorPos(window, 0.5f * display_w, 0.5f * display_h);
            mFlag = false;
        }

        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        mYaw += mSensitivity * static_cast<float>(xpos - 0.5f * display_w);
        mPitch += mSensitivity * static_cast<float>(ypos - 0.5f * display_h);

        if (mPitch < -89.0f) mPitch = -89.0f;
        if (mPitch > +89.0f) mPitch = +89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(-mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

        mFront = glm::normalize(front);

        glfwSetCursorPos(window, 0.5f * display_w, 0.5f * display_h);
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (!mFlag) {
            mFlag = true;
        }
    }
}

void Camera::SetViewMatrix(const Shader &shader, const char *name) const {
    const glm::mat4 view = glm::lookAt(mPosition, mPosition + mFront, mUp);
    shader.SetFloat4x4(name, view);
}

void Camera::SetProjectionMatrix(const Shader &shader, const char *name, float fovy, float aspect, float near, float far) const {
    const glm::mat4 projection = glm::perspective(fovy, aspect, near, far);
    shader.SetFloat4x4(name, projection);
}
