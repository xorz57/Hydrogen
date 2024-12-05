#version 330 core

uniform vec3 u_light_position;
uniform float u_light_strength;
uniform vec4 u_light_color;
uniform vec4 u_color;

in vec3 v_position;
in vec3 v_normal;

out vec4 f_color;

void main() {
    vec4 ambient = u_light_strength * u_light_color;

    vec3 light_direction = normalize(u_light_position - v_position);
    vec4 diffuse = max(dot(normalize(v_normal), light_direction), 0.0) * u_light_color;

    f_color = (ambient + diffuse) * u_color;
}
