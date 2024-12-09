#include "Capsule.hpp"

Capsule::Capsule() {
    Build(32, 32);

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

Capsule::Capsule(const std::uint32_t sectors, const std::uint32_t stacks) {
    Build(sectors, stacks);

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

void Capsule::Build(const std::uint32_t sectors, const std::uint32_t stacks) {
    constexpr float height = 0.5f;
    constexpr float radius = 0.5f;

    const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
    const float stack_step = glm::half_pi<float>() / static_cast<float>(stacks);

    // Top Hemisphere Vertices
    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_angle = static_cast<float>(stack) * stack_step;
        const float stack_radius = 0.5f * glm::sin(stack_angle);

        const float y = 0.5f * glm::cos(stack_angle) + height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = stack_radius * glm::cos(sector_angle);
            const float z = stack_radius * glm::sin(sector_angle);

            const glm::vec3 position(x, y, z);
            const glm::vec3 normal = glm::normalize(position - glm::vec3(0.0f, +height, 0.0f));

            mVertices.emplace_back(position, normal);
        }
    }

    // Bottom Hemisphere Vertices
    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_angle = glm::half_pi<float>() + static_cast<float>(stack) * stack_step;
        const float stack_radius = 0.5f * glm::sin(stack_angle);

        const float y = 0.5f * glm::cos(stack_angle) - height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = stack_radius * glm::cos(sector_angle);
            const float z = stack_radius * glm::sin(sector_angle);

            const glm::vec3 position(x, y, z);
            const glm::vec3 normal = glm::normalize(position - glm::vec3(0.0f, -height, 0.0f));

            mVertices.emplace_back(position, normal);
        }
    }

    // Cylinder Vertices
    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float sector_angle = static_cast<float>(sector) * sector_step;

        const float x = radius * glm::cos(sector_angle);
        const float z = radius * glm::sin(sector_angle);

        const glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));
        mVertices.emplace_back(glm::vec3(x, +height, z), normal);
        mVertices.emplace_back(glm::vec3(x, -height, z), normal);
    }

    const std::uint32_t hemisphere_offset = (stacks + 1) * (sectors + 1);

    // Top Hemisphere Indices
    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        const std::uint32_t k1 = stack * (sectors + 1);
        const std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements.push_back(k1 + sector);
            mElements.push_back(k2 + sector);
            mElements.push_back(k1 + sector + 1);

            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector);
            mElements.push_back(k2 + sector + 1);
        }
    }

    // Bottom Hemisphere Indices
    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        const std::uint32_t k1 = hemisphere_offset + stack * (sectors + 1);
        const std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements.push_back(k1 + sector);
            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector);

            mElements.push_back(k2 + sector);
            mElements.push_back(k1 + sector + 1);
            mElements.push_back(k2 + sector + 1);
        }
    }

    // Cylinder Indices
    const std::uint32_t cylinder_offset = hemisphere_offset * 2;
    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        const std::uint32_t top1 = cylinder_offset + sector * 2;
        const std::uint32_t top2 = top1 + 1;
        const std::uint32_t bottom1 = top1 + 2;
        const std::uint32_t bottom2 = bottom1 + 1;

        mElements.push_back(top1);
        mElements.push_back(bottom1);
        mElements.push_back(top2);

        mElements.push_back(top2);
        mElements.push_back(bottom1);
        mElements.push_back(bottom2);
    }
}

void Capsule::Draw() const {
    mVAO->Bind();
    mEBO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, nullptr);
    VAO::Unbind();
}

void Capsule::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
