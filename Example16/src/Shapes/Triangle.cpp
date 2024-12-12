#include "Triangle.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Triangle::Triangle() {
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

void Triangle::Draw() const {
    mVAO->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<std::int32_t>(mElements.size()), GL_UNSIGNED_INT, static_cast<void *>(nullptr));
    VAO::Unbind();
}

void Triangle::Delete() const {
    mVAO->Delete();
    mVBO->Delete();
    mEBO->Delete();
}
