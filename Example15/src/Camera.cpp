#include "Camera.hpp"

void Camera::SetViewMatrix(const Shader &shader, const char *name) const {
    const glm::mat4 view = glm::lookAt(mEye, mCenter, mUp);
    shader.SetFloat4x4(name, view);
}

void Camera::SetProjectionMatrix(const Shader &shader, const char *name, float aspect, float near, float far) const {
    const glm::mat4 projection = glm::perspective(mFOV, aspect, near, far);
    shader.SetFloat4x4(name, projection);
}
