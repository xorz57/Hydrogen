#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>
#include <memory>

template<typename T>
class VBO {
public:
    explicit VBO(const std::vector<T> &vertices);

    void Bind() const;
    void Delete() const;

    static std::shared_ptr<VBO<T>> Create(const std::vector<T> &vertices);
    static void Unbind();

private:
    std::uint32_t mID = 0;
};

#include "VBO.inl"
