#pragma once

#include "../EBO.hpp"
#include "../VAO.hpp"
#include "../VBO.hpp"
#include "../Vertex.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>
#include <vector>

class Triangle {
public:
    Triangle();

    void Draw() const;
    void Delete() const;

private:
    const std::vector<Vertex> mVertices{
            {{-0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, 1.0f}},
            {{+0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, 1.0f}},
            {{+0.0f, +0.5f, +0.0f}, {0.0f, 0.0f, 1.0f}},
    };

    const std::vector<GLuint> mElements{
            0,
            1,
            2,
    };

    std::shared_ptr<VAO> mVAO;
    std::shared_ptr<VBO<Vertex>> mVBO;
    std::shared_ptr<EBO<GLuint>> mEBO;
};
