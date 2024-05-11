#include "Triangle.hpp"

Triangle::Triangle() {
    mVAO.Bind();
    mVBO.Bind();
    mVAO.SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    mVAO.SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    mVBO.Unbind();
    mVAO.Unbind();
}

void Triangle::Draw() const {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    mTexture.Unbind();
    mVAO.Unbind();
}

void Triangle::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}
