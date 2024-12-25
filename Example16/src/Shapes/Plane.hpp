#pragma once

#include "../EBO.hpp"
#include "../VAO.hpp"
#include "../VBO.hpp"
#include "../Vertex.hpp"

#include <memory>
#include <vector>

class Plane {
public:
    Plane();
    Plane(std::uint32_t segments_x, std::uint32_t segments_z);
    void Draw() const;
    void Delete() const;

private:
    void Build(std::uint32_t segments_x, std::uint32_t segments_z);
    std::vector<Vertex> mVertices;
    std::vector<std::uint32_t> mElements;
    std::shared_ptr<VAO> mVAO;
    std::shared_ptr<VBO<Vertex>> mVBO;
    std::shared_ptr<EBO<std::uint32_t>> mEBO;
};
