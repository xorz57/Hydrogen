#include "Camera.hpp"

glm::mat4 Camera::GetView() const {
    return glm::lookAt(mEye, mCenter, mUp);
}

glm::mat4 Camera::GetProjection(float aspect) const {
    return glm::perspective(mFOV, aspect, mNear, mFar);
}
