#include "Plane.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Plane::Plane() {
    Build(2, 2);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<std::uint32_t>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<std::uint32_t>::Unbind();
    VAO::Unbind();
}

Plane::Plane(std::uint32_t segments_x, std::uint32_t segments_z) {
    Build(segments_x, segments_z);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<std::uint32_t>::Create(mElements);

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetVec3(0, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    VAO::SetVec3(1, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    VBO<std::uint32_t>::Unbind();
    VAO::Unbind();
}

void Plane::Build(const std::uint32_t segments_x, const std::uint32_t segments_z) {
    const float step_x = 1.0f / static_cast<float>(segments_x);
    const float step_z = 1.0f / static_cast<float>(segments_z);

    const glm::vec3 normal(0.0f, 1.0f, 0.0f);

    for (std::uint32_t i = 0; i <= segments_z; ++i) {
        for (std::uint32_t j = 0; j <= segments_x; ++j) {
            const float x = static_cast<float>(j) * step_x - 0.5f;
            const float z = static_cast<float>(i) * step_z - 0.5f;

            const glm::vec3 position(x, 0.0f, z);

            mVertices.push_back({position, normal});
        }
    }

    for (std::uint32_t i = 0; i < segments_z; ++i) {
        for (std::uint32_t j = 0; j < segments_x; ++j) {
            const std::uint32_t base = i * (segments_x + 1) + j;

            mElements.push_back(base);
            mElements.push_back(base + 1);
            mElements.push_back(base + segments_x + 1);

            mElements.push_back(base + segments_x + 1);
            mElements.push_back(base + 1);
            mElements.push_back(base + segments_x + 2);
        }
    }
}

void Plane::Draw() const {
    mVAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    VAO::Unbind();
}

void Plane::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
