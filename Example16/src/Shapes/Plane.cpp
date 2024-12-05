#include "Plane.hpp"

Plane::Plane() {
    Build(2, 2);

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

Plane::Plane(std::uint32_t segmentsX, std::uint32_t segmentsZ) {
    Build(segmentsX, segmentsZ);

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

void Plane::Build(const std::uint32_t segmentsX, const std::uint32_t segmentsZ) {
    const float stepX = 1.0f / static_cast<float>(segmentsX);
    const float stepZ = 1.0f / static_cast<float>(segmentsZ);

    mVertices.reserve((segmentsX + 1) * (segmentsZ + 1));
    const glm::vec3 normal = {0.0f, 1.0f, 0.0f};

    for (std::uint32_t i = 0; i <= segmentsZ; ++i) {
        for (std::uint32_t j = 0; j <= segmentsX; ++j) {
            const float x = static_cast<float>(j) * stepX - 0.5f;
            const float z = static_cast<float>(i) * stepZ - 0.5f;
            mVertices.push_back({{x, 0.0f, z}, normal});
        }
    }

    mElements.reserve(segmentsX * segmentsZ * 6);
    for (std::uint32_t i = 0; i < segmentsZ; ++i) {
        for (std::uint32_t j = 0; j < segmentsX; ++j) {
            const GLuint base = i * (segmentsX + 1) + j;

            mElements.push_back(base);
            mElements.push_back(base + 1);
            mElements.push_back(base + segmentsX + 1);

            mElements.push_back(base + segmentsX + 1);
            mElements.push_back(base + 1);
            mElements.push_back(base + segmentsX + 2);
        }
    }
}

void Plane::Draw() const {
    mVAO->Bind();

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));

    VAO::Unbind();
}

void Plane::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
