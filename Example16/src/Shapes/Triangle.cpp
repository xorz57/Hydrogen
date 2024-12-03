#include "Triangle.hpp"

Triangle::Triangle() {
    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Triangle::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));

    VAO::Unbind();
}

void Triangle::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
