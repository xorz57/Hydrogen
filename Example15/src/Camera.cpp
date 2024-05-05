#include "Camera.hpp"

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(mEye, mCenter, mUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspect) const {
    return glm::perspective(mFOV, aspect, mNear, mFar);
}
