#include "Triangle.hpp"

Triangle::Triangle() {
    mVAO.Bind();
    mVBO.Bind();
    mVAO.SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    mVAO.SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    mVBO.Unbind();
    mVAO.Unbind();
}

void Triangle::Draw() {
    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    mVAO.Unbind();
}

void Triangle::Delete() {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
