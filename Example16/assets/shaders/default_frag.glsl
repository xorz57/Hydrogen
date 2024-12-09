#version 330 core

struct Light {
    vec3 position;
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

in vec3 v_position;
in vec3 v_normal;

out vec4 f_color;

void main() {
    vec3 ambient = u_light.ambient * u_material.ambient;

    vec3 light_direction = normalize(u_light.position - v_position);
    vec3 diffuse = u_light.diffuse * max(dot(normalize(v_normal), light_direction), 0.0) * u_material.diffuse;

    vec3 camera_direction = normalize(u_camera_position - v_position);
    vec3 reflection_direction = reflect(-light_direction, normalize(v_normal));
    vec3 specular = u_light.specular * pow(max(dot(camera_direction, reflection_direction), 0.0), u_material.shininess) * u_material.specular;

    f_color = vec4(ambient + diffuse + specular, 1.0);
}
