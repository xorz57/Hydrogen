#include "Cylinder.hpp"

Cylinder::Cylinder() {
    Build(32);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO1 = EBO<GLuint>::Create(mElements1);
    mEBO2 = EBO<GLuint>::Create(mElements2);
    mEBO3 = EBO<GLuint>::Create(mElements3);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

Cylinder::Cylinder(std::uint32_t sectors) {
    Build(sectors);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO1 = EBO<GLuint>::Create(mElements1);
    mEBO2 = EBO<GLuint>::Create(mElements2);
    mEBO3 = EBO<GLuint>::Create(mElements3);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Cylinder::Build(std::uint32_t sectors) {
    mVertices.push_back({{0.0f, 0.5f, 0.0f}});
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float angle = 2.0f * glm::pi<float>() * static_cast<float>(sector) / static_cast<float>(sectors);
        const float x = 0.5f * glm::cos(angle);
        const float z = 0.5f * glm::sin(angle);
        mVertices.push_back({{x, 0.5f, z}});
    }
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        mElements1.push_back(0);
        mElements1.push_back(sector);
        mElements1.push_back(sector + 1);
    }

    size_t offset = mVertices.size();

    mVertices.push_back({{0.0f, -0.5f, 0.0f}});
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float angle = 2.0f * glm::pi<float>() * static_cast<float>(sector) / static_cast<float>(sectors);
        const float x = 0.5f * glm::cos(angle);
        const float z = 0.5f * glm::sin(angle);
        mVertices.push_back({{x, -0.5f, z}});
    }
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        mElements2.push_back(static_cast<GLuint>(offset));
        mElements2.push_back(static_cast<GLuint>(offset + sector + 1));
        mElements2.push_back(static_cast<GLuint>(offset + sector));
    }

    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        const std::uint32_t top1 = sector;
        const std::uint32_t top2 = sector + 1;
        const std::uint32_t bottom1 = static_cast<std::uint32_t>(offset) + sector;
        const std::uint32_t bottom2 = static_cast<std::uint32_t>(offset) + sector + 1;

        mElements3.push_back(top1);
        mElements3.push_back(bottom1);
        mElements3.push_back(top2);

        mElements3.push_back(top2);
        mElements3.push_back(bottom1);
        mElements3.push_back(bottom2);
    }
}

void Cylinder::Draw() const {
    mVAO->Bind();

    mEBO1->Bind();
    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mElements1.size()), GL_UNSIGNED_INT, nullptr);

    mEBO2->Bind();
    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mElements2.size()), GL_UNSIGNED_INT, nullptr);

    mEBO3->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements3.size()), GL_UNSIGNED_INT, nullptr);

    VAO::Unbind();
}

void Cylinder::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO1->Delete();
    mEBO2->Delete();
    mEBO3->Delete();
}
