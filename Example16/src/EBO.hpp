#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <vector>
#include <memory>

template<typename T>
class EBO {
public:
    explicit EBO(const std::vector<T> &elements);

    void Bind() const;
    void Delete() const;

    static std::shared_ptr<EBO<T>> Create(const std::vector<T> &elements);
    static void Unbind();

private:
    std::uint32_t mID = 0;
};

#include "EBO.inl"
