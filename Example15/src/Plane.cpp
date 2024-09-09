#include "Plane.hpp"

Plane::Plane() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetFloat2(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texture_coordinates)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Plane::Draw() const {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    Texture::Unbind();
    VAO::Unbind();
}

void Plane::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
