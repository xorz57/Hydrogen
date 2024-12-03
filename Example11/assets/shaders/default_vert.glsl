#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture_coordinates;

out vec2 v_texture_coordinates;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    v_texture_coordinates = a_texture_coordinates;
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
