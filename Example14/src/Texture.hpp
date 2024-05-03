#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Texture {
public:
    Texture(const char *texturePath);

    void Bind();
    void Unbind();
    void Delete();

private:
    GLuint mID = 0;
};
