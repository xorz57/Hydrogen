#include "Cube.hpp"

Cube::Cube() {
    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Cube::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));

    VAO::Unbind();
}

void Cube::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
