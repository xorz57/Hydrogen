#pragma once

#include "EBO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Vertex.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class Plane {
public:
    Plane();

    void Draw(Shader &shader);
    void Delete();
    void Scale(const glm::vec3 &v);
    void Translate(const glm::vec3 &v);
    void Rotate(float angle, const glm::vec3 &v);

private:
    const std::vector<Vertex> mVertices{
            {{-0.5f, +0.0f, -0.5f}, {+0.0f, +0.0f}},// 0
            {{+0.5f, +0.0f, -0.5f}, {+1.0f, +0.0f}},// 1
            {{-0.5f, +0.0f, +0.5f}, {+0.0f, +1.0f}},// 2
            {{+0.5f, +0.0f, +0.5f}, {+1.0f, +1.0f}},// 3
    };

    const std::vector<GLuint> mElements{
            0,// 0
            1,// 1
            2,// 2
            2,// 3
            1,// 4
            3,// 5
    };

    VAO mVAO;
    VBO mVBO{mVertices};
    EBO mEBO{mElements};

    Texture mTexture{"assets/textures/texture.png"};

    glm::mat4 mModel{1.0f};
};
