#include "Triangle.hpp"

Triangle::Triangle() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Triangle::Draw() const {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Triangle::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}

void Triangle::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Triangle::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Triangle::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}

void Triangle::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Triangle::GetModel() const {
    return mModel;
}
