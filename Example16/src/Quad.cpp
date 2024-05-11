#include "Quad.hpp"

Quad::Quad() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Quad::Draw() const {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Quad::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
