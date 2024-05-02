#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);
}

void VAO::Bind() const {
    glBindVertexArray(mID);
}

void VAO::Unbind() const {
    glBindVertexArray(0);
}

void VAO::Delete() const {
    glDeleteVertexArrays(1, &mID);
}

void VAO::SetVec2(GLuint index, GLsizei stride, void *pointer) const {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VAO::SetVec3(GLuint index, GLsizei stride, void *pointer) const {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, pointer);
}