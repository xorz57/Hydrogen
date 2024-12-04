#pragma once

#include "../EBO.hpp"
#include "../VAO.hpp"
#include "../VBO.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <vector>

class Cube {
public:
    Cube();

    void Draw() const;
    void Delete() const;

private:
    struct Vertex {
        glm::vec3 position;
    };

    const std::vector<Vertex> mVertices{
            {{-0.5f, -0.5f, -0.5f}},
            {{+0.5f, -0.5f, -0.5f}},
            {{+0.5f, +0.5f, -0.5f}},
            {{-0.5f, +0.5f, -0.5f}},

            {{-0.5f, -0.5f, +0.5f}},
            {{+0.5f, -0.5f, +0.5f}},
            {{+0.5f, +0.5f, +0.5f}},
            {{-0.5f, +0.5f, +0.5f}},

            {{-0.5f, +0.5f, +0.5f}},
            {{-0.5f, +0.5f, -0.5f}},
            {{-0.5f, -0.5f, -0.5f}},
            {{-0.5f, -0.5f, +0.5f}},

            {{+0.5f, +0.5f, +0.5f}},
            {{+0.5f, +0.5f, -0.5f}},
            {{+0.5f, -0.5f, -0.5f}},
            {{+0.5f, -0.5f, +0.5f}},

            {{-0.5f, -0.5f, -0.5f}},
            {{+0.5f, -0.5f, -0.5f}},
            {{+0.5f, -0.5f, +0.5f}},
            {{-0.5f, -0.5f, +0.5f}},

            {{-0.5f, +0.5f, -0.5f}},
            {{+0.5f, +0.5f, -0.5f}},
            {{+0.5f, +0.5f, +0.5f}},
            {{-0.5f, +0.5f, +0.5f}},
    };

    const std::vector<GLuint> mElements{
            0,   1,  2,  2,  3,  0,
            4,   5,  6,  6,  7,  4,
            8,   9, 10, 10, 11,  8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20,
    };

    std::shared_ptr<VAO> mVAO;
    std::shared_ptr<VBO<Vertex>> mVBO;
    std::shared_ptr<EBO<GLuint>> mEBO;
};
