#pragma once

#include "VBO.hpp"

template<typename T>
VBO<T>::VBO(const std::vector<T> &vertices) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ARRAY_BUFFER, mID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<std::uint64_t>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
}

template<typename T>
void VBO<T>::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

template<typename T>
void VBO<T>::Delete() const {
    glDeleteBuffers(1, &mID);
}

template<typename T>
std::shared_ptr<VBO<T>> VBO<T>::Create(const std::vector<T> &vertices) {
    return std::make_shared<VBO<T>>(vertices);
}

template<typename T>
void VBO<T>::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
