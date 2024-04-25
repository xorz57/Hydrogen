#version 330 core

out vec4 fragCol;
in vec3 vertCol;

void main() {
    fragCol = vec4(vertCol, 1.0);
}