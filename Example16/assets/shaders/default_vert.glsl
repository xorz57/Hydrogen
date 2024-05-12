#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;

out vec2 v_texture_coordinates;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
    v_texture_coordinates = texture_coordinates;
}
