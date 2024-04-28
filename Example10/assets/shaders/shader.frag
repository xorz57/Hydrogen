#version 330 core

out vec4 f_Color;
in vec3 v_Color;
in vec2 v_TextureCoordinates;

uniform sampler2D u_Texture;

void main() {
    f_Color = texture(u_Texture, v_TextureCoordinates) * vec4(v_Color, 1.0);
}
