#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);
}

std::shared_ptr<VAO> VAO::Create() {
    return std::make_shared<VAO>();
}

void VAO::Bind() const {
    glBindVertexArray(mID);
}

void VAO::Delete() const {
    glDeleteVertexArrays(1, &mID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::SetFloat(const std::uint32_t index, const std::int32_t stride, const void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VAO::SetFloat2(const std::uint32_t index, const std::int32_t stride, const void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VAO::SetVec3(const std::uint32_t index, const std::int32_t stride, const void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, pointer);
}
