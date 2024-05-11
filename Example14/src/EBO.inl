#include "EBO.hpp"

template<typename T>
EBO<T>::EBO(const std::vector<T> &elements) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(T)), elements.data(), GL_STATIC_DRAW);
}

template<typename T>
void EBO<T>::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

template<typename T>
void EBO<T>::Delete() const {
    glDeleteBuffers(1, &mID);
}

template<typename T>
void EBO<T>::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
