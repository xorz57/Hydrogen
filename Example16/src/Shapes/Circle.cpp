#include "Circle.hpp"

Circle::Circle() {
    Build(32);

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

Circle::Circle(std::uint32_t sectors) {
    Build(sectors);

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

void Circle::Build(std::uint32_t sectors) {
    mVertices.reserve(sectors + 2);
    mElements.reserve(sectors + 2);

    mVertices.push_back({{0.0f, 0.0f, 0.0f}, {0.5f, 0.5f}});
    mElements.push_back(0);

    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
        const float sector_angle = static_cast<float>(sector) * sector_step;
        const float x = 0.5f * glm::cos(sector_angle);
        const float y = 0.5f * glm::sin(sector_angle);
        const float u = 0.5f + 0.5f * glm::cos(sector_angle);
        const float v = 0.5f + 0.5f * glm::sin(sector_angle);
        mVertices.push_back({{x, y, 0.0f}, {u, v}});
        mElements.push_back(sector + 1);
    }
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
