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
    shader.Use();
    shader.UploadFloat4x4("u_Model", mModel);

    mModel = glm::mat4(1.0f);

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

void Cube::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Cube::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Cube::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}
