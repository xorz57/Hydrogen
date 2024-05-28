#include "Plane.hpp"

Plane::Plane(std::uint32_t grid_x, std::uint32_t grid_z) {
    const float step_x = 1.0f / static_cast<float>(grid_x);
    const float step_z = 1.0f / static_cast<float>(grid_z);

    mVertices.reserve((grid_x + 1) * (grid_z + 1));
    for (std::uint32_t i = 0; i <= grid_z; ++i) {
        for (std::uint32_t j = 0; j <= grid_x; ++j) {
            const float x = static_cast<float>(j) * step_x - 0.5f;
            const float z = static_cast<float>(i) * step_z - 0.5f;
            const float u = static_cast<float>(j) * step_x;
            const float v = static_cast<float>(i) * step_z;
            mVertices.push_back({glm::vec3(x, 0.0f, z), glm::vec2(u, v)});
        }
    }

    mElements.reserve(grid_x * grid_z * 6);
    for (std::uint32_t i = 0; i < grid_z; ++i) {
        for (std::uint32_t j = 0; j < grid_x; ++j) {
            const GLuint base = i * (grid_x + 1) + j;
            mElements.push_back(base);
            mElements.push_back(base + 1);
            mElements.push_back(base + grid_x + 1);
            mElements.push_back(base + grid_x + 1);
            mElements.push_back(base + 1);
            mElements.push_back(base + grid_x + 2);
        }
    }

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/texture_gray.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
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
