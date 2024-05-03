#include "Cube.hpp"

Cube::Cube() {
    mVBO.Bind();
    mVAO.SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    mVAO.SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, textureCoordinates));
    mVBO.Unbind();
}

void Cube::Draw(Shader &shader) {
    shader.SetFloat4x4("u_Model", mModel);

    mModel = glm::mat4(1.0f);

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
}

void Cube::Delete() {
    mVAO.Delete();
    mVBO.Delete();
    mEBO.Delete();
}

void Cube::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Cube::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Cube::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}