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

uniform Light u_Light;
uniform Material u_Material;

uniform vec3 u_CameraPosition;

in vec3 v_Position;
in vec3 v_Normal;

out vec4 f_Color;

void main() {
    vec3 ambient = u_Light.ambient * u_Material.ambient;

    vec3 lightDirection = normalize(u_Light.position - v_Position);
    vec3 diffuse = u_Light.diffuse * max(dot(normalize(v_Normal), lightDirection), 0.0) * u_Material.diffuse;

    vec3 cameraDirection = normalize(u_CameraPosition - v_Position);
    vec3 reflectionDirection = reflect(-lightDirection, normalize(v_Normal));
    vec3 specular = u_Light.specular * pow(max(dot(cameraDirection, reflectionDirection), 0.0), u_Material.shininess) * u_Material.specular;

    f_Color = vec4(ambient + diffuse + specular, 1.0);
}
