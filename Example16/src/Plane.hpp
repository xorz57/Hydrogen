#pragma once

#include "EBO.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include "VBO.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Plane {
public:
    Plane();

    void Draw() const;
    void Delete() const;

    [[nodiscard]] glm::mat4 GetModel() const;

    void Scale(const glm::vec3 &v);
    void Translate(const glm::vec3 &v);
    void Rotate(float angle, const glm::vec3 &v);
    void Reset();

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texture_coordinates;
    };

    const std::vector<Vertex> mVertices{
            {{-1.0f, +0.0f, -1.0f}, {+0.0f, +0.0f}},// 0
            {{+1.0f, +0.0f, -1.0f}, {+1.0f, +0.0f}},// 1
            {{-1.0f, +0.0f, +1.0f}, {+0.0f, +1.0f}},// 2
            {{+1.0f, +0.0f, +1.0f}, {+1.0f, +1.0f}},// 3
    };

    const std::vector<GLuint> mElements{
            0,// 0
            1,// 1
            2,// 2
            2,// 3
            1,// 4
            3,// 5
    };

    glm::mat4 mModel{1.0f};

    VAO mVAO;
    VBO<Vertex> mVBO{mVertices};
    EBO<GLuint> mEBO{mElements};
    Texture mTexture{"assets/textures/texture.png"};
};
