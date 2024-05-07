#include "Cube.hpp"

Cube::Cube() {
    mVAO.Bind();
    mVBO.Bind();
    mVAO.SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    mVAO.SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    mVBO.Unbind();
    mVAO.Unbind();
}

void Cube::Draw(Shader &shader) {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    mTexture.Unbind();
    mVAO.Unbind();
}

void Cube::Delete() {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
