#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coordinates;

out vec2 v_texture_coordinates;

void main() {
    gl_Position = vec4(a_position, 1.0);
    v_texture_coordinates = a_texture_coordinates;
}
