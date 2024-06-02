#include "Sphere.hpp"

Sphere::Sphere() {
    Build(32, 32);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/sphere.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

Sphere::Sphere(std::uint32_t sectors, std::uint32_t stacks) {
    Build(sectors, stacks);

    mVAO = VAO::Create();
    mVBO = VBO<Vertex>::Create(mVertices);
    mEBO = EBO<GLuint>::Create(mElements);
    mTexture = Texture::Create("assets/textures/sphere.png");

    mVAO->Bind();
    mVBO->Bind();
    VAO::SetFloat3(0, sizeof(Vertex), (void *) offsetof(Vertex, position));
    VAO::SetFloat2(1, sizeof(Vertex), (void *) offsetof(Vertex, texture_coordinates));
    VBO<GLuint>::Unbind();
    VAO::Unbind();
}

void Sphere::Build(std::uint32_t sectors, std::uint32_t stacks) {
    for (std::uint32_t i = 0; i <= stacks; ++i) {
        const float stack_step = glm::pi<float>() / static_cast<float>(stacks);
        const float stack_angle = static_cast<float>(i) * stack_step;

        const float y = glm::cos(stack_angle);

        for (std::uint32_t j = 0; j <= sectors; ++j) {
            const float sector_step = 2.0f * glm::pi<float>() / static_cast<float>(sectors);
            const float sector_angle = static_cast<float>(j) * sector_step;

            const float x = glm::sin(stack_angle) * glm::cos(sector_angle);
            const float z = glm::sin(stack_angle) * glm::sin(sector_angle);

            const float u = static_cast<float>(j) / static_cast<float>(sectors);
            const float v = static_cast<float>(i) / static_cast<float>(stacks);

            mVertices.push_back({{0.5f * x, 0.5f * y, 0.5f * z}, {u, v}});
        }
    }

    for (std::uint32_t i = 0; i < stacks; ++i) {
        std::uint32_t k1 = i * (sectors + 1);
        std::uint32_t k2 = k1 + sectors + 1;

        for (std::uint32_t j = 0; j < sectors; ++j) {
            if (i != 0) {
                mElements.push_back(k1);
                mElements.push_back(k2);
                mElements.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                mElements.push_back(k1 + 1);
                mElements.push_back(k2);
                mElements.push_back(k2 + 1);
            }

            ++k1;
            ++k2;
        }
    }
}

void Sphere::Draw() const {
    mVAO->Bind();
    mTexture->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mElements.size()), GL_UNSIGNED_INT, (void *) nullptr);
    Texture::Unbind();
    VAO::Unbind();
}

void Sphere::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}

void Sphere::Scale(const glm::vec3 &v) {
    mModel = glm::scale(mModel, v);
}

void Sphere::Translate(const glm::vec3 &v) {
    mModel = glm::translate(mModel, v);
}

void Sphere::Rotate(float angle, const glm::vec3 &v) {
    mModel = glm::rotate(mModel, angle, v);
}

void Sphere::Reset() {
    mModel = glm::mat4(1.0f);
}

glm::mat4 Sphere::GetModel() const {
    return mModel;
}
