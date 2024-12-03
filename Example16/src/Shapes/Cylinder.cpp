#include "Cylinder.hpp"

Cylinder::Cylinder() {
    Build(32);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);

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
    mEBO = EBO<GLuint>::Create(mElements);

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

    mTopCapRange.start = mElements.size();
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        mElements.push_back(0);
        mElements.push_back(sector);
        mElements.push_back(sector + 1);
    }
    mTopCapRange.count = mElements.size() - mTopCapRange.start;

    size_t offset = mVertices.size();

    mVertices.push_back({{0.0f, -0.5f, 0.0f}});

    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float angle = 2.0f * glm::pi<float>() * static_cast<float>(sector) / static_cast<float>(sectors);
        const float x = 0.5f * glm::cos(angle);
        const float z = 0.5f * glm::sin(angle);
        mVertices.push_back({{x, -0.5f, z}});
    }

    mBottomCapRange.start = mElements.size();
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        mElements.push_back(static_cast<GLuint>(offset));
        mElements.push_back(static_cast<GLuint>(offset + sector + 1));
        mElements.push_back(static_cast<GLuint>(offset + sector));
    }
    mBottomCapRange.count = mElements.size() - mBottomCapRange.start;

    mSideRange.start = mElements.size();
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        const std::uint32_t top1 = sector;
        const std::uint32_t top2 = sector + 1;
        const std::uint32_t bottom1 = static_cast<std::uint32_t>(offset) + sector;
        const std::uint32_t bottom2 = static_cast<std::uint32_t>(offset) + sector + 1;

        mElements.push_back(top1);
        mElements.push_back(bottom1);
        mElements.push_back(top2);

        mElements.push_back(top2);
        mElements.push_back(bottom1);
        mElements.push_back(bottom2);
    }
    mSideRange.count = mElements.size() - mSideRange.start;
}

void Cylinder::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mTopCapRange.count), GL_UNSIGNED_INT, reinterpret_cast<void *>(mTopCapRange.start * sizeof(GLuint)));
    glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(mBottomCapRange.count), GL_UNSIGNED_INT, reinterpret_cast<void *>(mBottomCapRange.start * sizeof(GLuint)));
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mSideRange.count), GL_UNSIGNED_INT, reinterpret_cast<void *>(mSideRange.start * sizeof(GLuint)));

    VAO::Unbind();
}

void Cylinder::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
