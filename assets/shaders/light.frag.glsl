#version 330 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_Light;

out vec4 f_Color;

void main() {
    f_Color = vec4(u_Light.ambient, 1.0f);
}
