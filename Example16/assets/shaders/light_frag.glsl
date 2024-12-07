#version 330 core

uniform vec3 u_color;

out vec3 f_color;

void main() {
    f_color = u_color;
}
