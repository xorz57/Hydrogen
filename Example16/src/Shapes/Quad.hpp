#pragma once

#include "../EBO.hpp"
#include "../VAO.hpp"
#include "../VBO.hpp"
#include "../Vertex.hpp"

#include <memory>
#include <vector>

class Quad {
public:
    Quad();

    void Draw() const;
    void Delete() const;

private:
    const std::vector<Vertex> mVertices{
            {{-0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, +1.0f}},
            {{+0.5f, -0.5f, +0.0f}, {0.0f, 0.0f, +1.0f}},
            {{-0.5f, +0.5f, +0.0f}, {0.0f, 0.0f, +1.0f}},
            {{+0.5f, +0.5f, +0.0f}, {0.0f, 0.0f, +1.0f}},
    };

    const std::vector<std::uint32_t> mElements{
            0,
            1,
            2,
            2,
            1,
            3,
    };

    std::shared_ptr<VAO> mVAO;
    std::shared_ptr<VBO<Vertex>> mVBO;
    std::shared_ptr<EBO<std::uint32_t>> mEBO;
};
