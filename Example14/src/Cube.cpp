#include "Cube.hpp"

Cube::Cube() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec2(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texture_coordinates)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Cube::Draw() const {
    mTexture.Bind();
    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    VAO::Unbind();
    Texture::Unbind();
}

void Cube::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
