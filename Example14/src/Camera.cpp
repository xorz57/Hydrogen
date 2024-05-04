#include "Camera.hpp"

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(mEye, mCenter, mUp);
}

glm::mat4 Camera::GetProjectionMatrix(float fovy, float aspect, float near, float far) const {
    return glm::perspective(fovy, aspect, near, far);
}
