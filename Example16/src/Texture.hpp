#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Texture {
public:
    explicit Texture(const char *texturePath);

    void Bind() const;
    static void Unbind();
    void Delete() const;

private:
    GLuint mID = 0;
};
