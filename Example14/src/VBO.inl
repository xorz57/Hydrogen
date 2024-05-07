#include "VBO.hpp"

template<typename T>
VBO<T>::VBO(const std::vector<T> &vertices) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ARRAY_BUFFER, mID);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(T)), vertices.data(), GL_STATIC_DRAW);
}

template<typename T>
void VBO<T>::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, mID);
}

template<typename T>
void VBO<T>::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void VBO<T>::Delete() const {
    glDeleteBuffers(1, &mID);
}
