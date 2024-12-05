#include "Circle.hpp"

Circle::Circle() {
    Build(32);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetFloat3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

Circle::Circle(const std::uint32_t sectors) {
    Build(sectors);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetFloat3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Circle::Build(const std::uint32_t sectors) {
    const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);

    mVertices.reserve(sectors + 2);
    mElements.reserve(sectors + 2);

    mVertices.push_back({{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
    mElements.push_back(0);

    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float sector_angle = static_cast<float>(sector) * sector_step;
        const float x = 0.5f * glm::cos(sector_angle);
        const float y = 0.5f * glm::sin(sector_angle);
        mVertices.push_back({{x, y, 0.0f}, {0.0f, 0.0f, 1.0f}});
        mElements.push_back(sector + 1);
    }
}

void Circle::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));

    VAO::Unbind();
}

void Circle::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
