#include "Cube.hpp"

Cube::Cube() {
    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/cube.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Cube::Draw() const {
    mVAO->Bind();
    mTexture->Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);

    Texture::Unbind();
    VAO::Unbind();
}

void Cube::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
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

void Cube::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Cube::GetModel() const {
    return mModel;
}
