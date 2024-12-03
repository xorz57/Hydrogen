#include "Capsule.hpp"

Capsule::Capsule() {
    Build(32, 16);

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

Capsule::Capsule(const std::uint32_t sectors, const std::uint32_t stacks) {
    Build(sectors, stacks);

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

void Capsule::Build(const std::uint32_t sectors, const std::uint32_t stacks) {
    constexpr float height = 0.5f;

    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_step = glm::half_pi<float>() / static_cast<float>(stacks);
        const float stack_angle = static_cast<float>(stack) * stack_step;

        const float y = 0.5f * glm::cos(stack_angle) + height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = 0.5f * glm::sin(stack_angle) * glm::cos(sector_angle);
            const float z = 0.5f * glm::sin(stack_angle) * glm::sin(sector_angle);

            mVertices.push_back({{x, y, z}});
        }
    }

    for (std::uint32_t stack = 0; stack <= stacks; ++stack) {
        const float stack_step = glm::half_pi<float>() / static_cast<float>(stacks);
        const float stack_angle = glm::half_pi<float>() + static_cast<float>(stack) * stack_step;

        const float y = 0.5f * glm::cos(stack_angle) - height;

        for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
            const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
            const float sector_angle = static_cast<float>(sector) * sector_step;

            const float x = 0.5f * glm::sin(stack_angle) * glm::cos(sector_angle);
            const float z = 0.5f * glm::sin(stack_angle) * glm::sin(sector_angle);

            mVertices.push_back({{x, y, z}});
        }
    }

    for (std::uint32_t sector = 0; sector <= sectors; ++sector) {
        const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
        const float sector_angle = static_cast<float>(sector) * sector_step;

        const float x = 0.5f * glm::cos(sector_angle);
        const float z = 0.5f * glm::sin(sector_angle);

        mVertices.push_back({{x, height, z}});
        mVertices.push_back({{x, -height, z}});
    }

    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        std::uint32_t k1 = stack * (sectors + 1);
        std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements1.push_back(k1);
            mElements1.push_back(k2);
            mElements1.push_back(k1 + 1);

            mElements1.push_back(k1 + 1);
            mElements1.push_back(k2);
            mElements1.push_back(k2 + 1);

            ++k1;
            ++k2;
        }
    }

    const std::uint32_t offset1 = (stacks + 1) * (sectors + 1);
    for (std::uint32_t stack = 0; stack < stacks; ++stack) {
        std::uint32_t k1 = offset1 + stack * (sectors + 1);
        std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t sector = 0; sector < sectors; ++sector) {
            mElements2.push_back(k1);
            mElements2.push_back(k1 + 1);
            mElements2.push_back(k2);

            mElements2.push_back(k2);
            mElements2.push_back(k1 + 1);
            mElements2.push_back(k2 + 1);

            ++k1;
            ++k2;
        }
    }

    const std::uint32_t offset2 = offset1 + (stacks + 1) * (sectors + 1);
    for (std::uint32_t sector = 0; sector < sectors; ++sector) {
        const std::uint32_t top1 = offset2 + sector * 2;
        const std::uint32_t top2 = top1 + 1;
        const std::uint32_t bottom1 = top1 + 2;
        const std::uint32_t bottom2 = bottom1 + 1;

        mElements3.push_back(top1);
        mElements3.push_back(bottom1);
        mElements3.push_back(top2);

        mElements3.push_back(top2);
        mElements3.push_back(bottom1);
        mElements3.push_back(bottom2);
    }
}

void Capsule::Draw() const {
    mVAO->Bind();

    mEBO1->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements1.size()), GL_UNSIGNED_INT, nullptr);

    mEBO2->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements2.size()), GL_UNSIGNED_INT, nullptr);

    mEBO3->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements3.size()), GL_UNSIGNED_INT, nullptr);

    VAO::Unbind();
}

void Capsule::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO1->Delete();
    mEBO2->Delete();
    mEBO3->Delete();
}
