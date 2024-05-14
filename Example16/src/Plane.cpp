#include "Plane.hpp"

Plane::Plane() {
    mVAO.Bind();
    mVBO.Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Plane::Draw() const {
    mVAO.Bind();
    mTexture.Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Plane::Delete() const {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}

void Plane::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Plane::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Plane::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}

void Plane::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Plane::GetModel() const {
    return mModel;
}
