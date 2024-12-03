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

class Circle {
public:
    Circle();
    explicit Circle(std::uint32_t sectors);

    void Draw() const;
    void Delete() const;

private:
    void Build(std::uint32_t sectors);

    struct Vertex {
        glm::vec3 position;
    };

    std::vector<Vertex> mVertices;

    std::vector<GLuint> mElements;

    std::shared_ptr<VAO> mVAO;
    std::shared_ptr<VBO<Vertex>> mVBO;
    std::shared_ptr<EBO<GLuint>> mEBO;
};
