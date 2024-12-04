#version 330 core

out vec4 f_color;
in vec2 v_texture_coordinates;

uniform float u_light_strength;
uniform vec4 u_light_color;
uniform vec4 u_color;

void main() {
    f_color = u_light_strength * u_light_color * u_color;
}
