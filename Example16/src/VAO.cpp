#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &mID);
    glBindVertexArray(mID);
}

void VAO::Bind() const {
    glBindVertexArray(mID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() const {
    glDeleteVertexArrays(1, &mID);
}

void VAO::SetFloat(GLuint index, GLsizei stride, void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VAO::SetFloat2(GLuint index, GLsizei stride, void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VAO::SetFloat3(GLuint index, GLsizei stride, void *pointer) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, pointer);
}
