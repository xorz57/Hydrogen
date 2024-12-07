#version 330 core

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light u_light;
uniform Material u_material;

uniform vec3 u_camera_position;
uniform vec3 u_light_position;
uniform vec3 u_color;

in vec3 v_position;
in vec3 v_normal;

out vec3 f_color;

void main() {
    vec3 ambient = u_material.ambient * u_light.ambient;

    vec3 light_direction = normalize(u_light_position - v_position);
    vec3 diffuse = max(dot(normalize(v_normal), light_direction), 0.0) * u_material.diffuse * u_light.diffuse;

    vec3 view_direction = normalize(u_camera_position - v_position);
    vec3 reflection_direction = reflect(-light_direction, normalize(v_normal));
    vec3 specular = u_material.specular * pow(max(dot(view_direction, reflection_direction), 0.0), u_material.shininess) * u_light.specular;

    f_color = (ambient + diffuse + specular) * u_color;
}
