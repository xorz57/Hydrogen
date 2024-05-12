#include "Cube.hpp"

Cube::Cube() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Cube::Draw() const {
    mTexture.Bind();
    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    VAO::Unbind();
    Texture::Unbind();
}

void Cube::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
