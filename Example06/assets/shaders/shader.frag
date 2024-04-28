#version 330 core

out vec4 f_Color;
in vec3 v_Color;

void main() {
    f_Color = vec4(v_Color, 1.0);
}
