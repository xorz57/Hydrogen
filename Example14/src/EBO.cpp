#include "EBO.hpp"

EBO::EBO(const std::vector<GLint> &elements) {
    glGenBuffers(1, &mID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(GLfloat)), elements.data(), GL_STATIC_DRAW);
}

void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void EBO::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const {
    glDeleteBuffers(1, &mID);
}
