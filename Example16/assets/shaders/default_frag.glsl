#version 330 core

uniform vec3 u_camera_position;
uniform float u_ambient_strength;
uniform float u_specular_strength;
uniform float u_shininess;
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform vec3 u_color;

in vec3 v_position;
in vec3 v_normal;

out vec3 f_color;

void main() {
    vec3 ambient = u_ambient_strength * u_light_color;

    vec3 light_direction = normalize(u_light_position - v_position);
    vec3 diffuse = max(dot(normalize(v_normal), light_direction), 0.0) * u_light_color;

    vec3 view_direction = normalize(u_camera_position - v_position);
    vec3 reflection_direction = reflect(-light_direction, normalize(v_normal));
    vec3 specular = u_specular_strength * pow(max(dot(view_direction, reflection_direction), 0.0), u_shininess) * u_light_color;

    f_color = (ambient + diffuse + specular) * u_color;
}
