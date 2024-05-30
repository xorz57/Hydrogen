#include "Circle.hpp"

Circle::Circle(std::uint32_t count) {
    mVertices.clear();
    mElements.clear();

    mVertices.reserve(count + 2);
    mElements.reserve(count + 2);

    mVertices.push_back({{0.0f, 0.0f, 0.0f}, {0.5f, 0.5f}});
    mElements.push_back(0);

    for (std::uint32_t i = 0; i <= count; ++i) {
        float angle = static_cast<float>(i) / static_cast<float>(count) * 2.0f * glm::pi<float>();
        float x = 0.5f * glm::cos(angle);
        float y = 0.5f * glm::sin(angle);
        float u = 0.5f + 0.5f * glm::cos(angle);
        float v = 0.5f + 0.5f * glm::sin(angle);
        mVertices.push_back({{x, y, 0.0f}, {u, v}});
        mElements.push_back(i + 1);
    }

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/purple.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Circle::Draw() const {
    mVAO->Bind();
    mTexture->Bind();
    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Circle::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}

void Circle::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Circle::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Circle::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}

void Circle::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Circle::GetModel() const {
    return mModel;
}
