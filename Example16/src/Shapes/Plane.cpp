#include "Plane.hpp"

Plane::Plane() {
    Build(16, 16);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/plane.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

Plane::Plane(std::uint32_t count_x, std::uint32_t count_z) {
    Build(count_x, count_z);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/plane.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Plane::Build(std::uint32_t count_x, std::uint32_t count_z) {
    const float step_x = 1.0f / static_cast<float>(count_x);
    const float step_z = 1.0f / static_cast<float>(count_z);

    mVertices.reserve((count_x + 1) * (count_z + 1));
    for (std::uint32_t i = 0; i <= count_z; ++i) {
        for (std::uint32_t j = 0; j <= count_x; ++j) {
            const float x = static_cast<float>(j) * step_x - 0.5f;
            const float z = static_cast<float>(i) * step_z - 0.5f;
            const float u = static_cast<float>(j) * step_x;
            const float v = static_cast<float>(i) * step_z;
            mVertices.push_back({{x, 0.0f, z}, {u, v}});
        }
    }

    mElements.reserve(count_x * count_z * 6);
    for (std::uint32_t i = 0; i < count_z; ++i) {
        for (std::uint32_t j = 0; j < count_x; ++j) {
            const GLuint base = i * (count_x + 1) + j;
            mElements.push_back(base);
            mElements.push_back(base + 1);
            mElements.push_back(base + count_x + 1);
            mElements.push_back(base + count_x + 1);
            mElements.push_back(base + 1);
            mElements.push_back(base + count_x + 2);
        }
    }
}

void Plane::Draw() const {
    mVAO->Bind();
    mTexture->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Plane::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}

void Plane::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Plane::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Plane::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}

void Plane::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Plane::GetModel() const {
    return mModel;
}
