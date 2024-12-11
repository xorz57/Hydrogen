#include "Circle.hpp"

Circle::Circle() {
    Build(32);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
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
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Circle::Build(const std::uint32_t sectors) {
    const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);

    mVertices.push_back({glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)});

    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        const float sector_angle = static_cast<float>(sector) * sector_step;
        const float x = 0.5f * glm::cos(sector_angle);
        const float y = 0.5f * glm::sin(sector_angle);
        mVertices.push_back({glm::vec3(x, y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)});

        GLuint current = sector + 1;
        GLuint next = (sector + 1) % sectors + 1;

        mElements.push_back(0);
        mElements.push_back(current);
        mElements.push_back(next);
    }
}

void Circle::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));

    VAO::Unbind();
}

void Circle::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
