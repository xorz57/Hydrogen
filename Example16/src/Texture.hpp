#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>

class Texture {
public:
    explicit Texture(const char *texturePath);

    void Bind() const;
    void Delete() const;

    static std::shared_ptr<Texture> Create(const char *texturePath);
    static void Unbind();

private:
    GLuint mID = 0;
};
