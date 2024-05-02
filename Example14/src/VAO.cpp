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
