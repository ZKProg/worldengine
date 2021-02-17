#version 450 core

in vec3 normal_vertex;
in vec3 position_vertex;

out vec4 color;

void main (void)
{
    vec3 sunlight = vec3(-1, 1, 1);

    vec3 suncolor = vec3(1, 1, 0);
    vec3 ambient = vec3(1, 0, 0);

    vec3 n_sun = normalize(sunlight);
    vec3 n_norm = normalize(normal_vertex);

    float diff = max(dot(n_sun, n_norm), 0.0);

    color = diff * vec4(1, 0, 0, 1);
}