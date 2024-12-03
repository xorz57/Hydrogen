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

Cylinder::Cylinder(const std::uint32_t sectors) {
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

void Cylinder::Build(const std::uint32_t sectors) {
    constexpr float height = 0.5f;
    const float radius = 0.5f;

    // Bottom center vertex
    mVertices.push_back({{0.0f, -height, 0.0f}});

    // Bottom circle vertices
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float angle = 2.0f * glm::pi<float>() * sector / sectors;
        const float x = radius * glm::cos(angle);
        const float z = radius * glm::sin(angle);
        mVertices.push_back({{x, -height, z}});
    }

    // Top center vertex
    mVertices.push_back({{0.0f, height, 0.0f}});

    // Top circle vertices
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float angle = 2.0f * glm::pi<float>() * sector / sectors;
        const float x = radius * glm::cos(angle);
        const float z = radius * glm::sin(angle);
        mVertices.push_back({{x, height, z}});
    }

    // Indices for bottom circle
    const GLuint bottom_center = 0;
    for (std::uint32_t sector = 1; sector <= sectors; ++sector) {
        mElements.push_back(bottom_center);
        mElements.push_back(sector);
        mElements.push_back(sector + 1);
    }

    // Indices for top circle
    const std::uint32_t top_center = sectors + 2;
    const std::uint32_t top_offset = sectors + 3;
    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        mElements.push_back(top_center);
        mElements.push_back(top_offset + sector);
        mElements.push_back(top_offset + sector + 1);
    }

    // Indices for cylinder sides
    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        const std::uint32_t bottom1 = 1 + sector;
        const std::uint32_t bottom2 = bottom1 + 1;
        const std::uint32_t top1 = top_offset + sector;
        const std::uint32_t top2 = top1 + 1;

        mElements.push_back(bottom1);
        mElements.push_back(bottom2);
        mElements.push_back(top1);

        mElements.push_back(top1);
        mElements.push_back(bottom2);
        mElements.push_back(top2);
    }
}

void Cylinder::Draw() const {
    mVAO->Bind();
    mEBO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, nullptr);
    VAO::Unbind();
}

void Cylinder::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
