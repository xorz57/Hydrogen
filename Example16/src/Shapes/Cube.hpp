#pragma once

#include "../EBO.hpp"
#include "../VAO.hpp"
#include "../VBO.hpp"
#include "../Vertex.hpp"

#include <vector>

class Cube {
public:
    Cube();

    void Draw() const;
    void Delete() const;

private:
    const std::vector<Vertex> mVertices{
            // Front Face
            {{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
            {{+0.5f, -0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
            {{+0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},
            {{-0.5f, +0.5f, +0.5f}, {0.0f, 0.0f, +1.0f}},

            // Back Face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
            {{+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
            {{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
            {{-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},

            // Left Face
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f, -0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f, +0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}},
            {{-0.5f, +0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},

            // Right Face
            {{+0.5f, -0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}},
            {{+0.5f, -0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}},
            {{+0.5f, +0.5f, +0.5f}, {+1.0f, 0.0f, 0.0f}},
            {{+0.5f, +0.5f, -0.5f}, {+1.0f, 0.0f, 0.0f}},

            // Bottom Face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
            {{+0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
            {{+0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}},
            {{-0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}},

            // Top Face
            {{-0.5f, +0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}},
            {{+0.5f, +0.5f, -0.5f}, {0.0f, +1.0f, 0.0f}},
            {{+0.5f, +0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}},
            {{-0.5f, +0.5f, +0.5f}, {0.0f, +1.0f, 0.0f}},
    };

    const std::vector<std::uint32_t> mElements{
            0, 1, 2, 2, 3, 0,      // Front Face
            4, 5, 6, 6, 7, 4,      // Back Face
            8, 9, 10, 10, 11, 8,   // Left Face
            12, 13, 14, 14, 15, 12,// Right Face
            16, 17, 18, 18, 19, 16,// Bottom Face
            20, 21, 22, 22, 23, 20 // Top Face
    };

    VAO mVAO;
    VBO<Vertex> mVBO{mVertices};
    EBO<std::uint32_t> mEBO{mElements};
};
