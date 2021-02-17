#version 450 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;

out vec3 normal_vertex;
out vec3 position_vertex;

void main (void)
{
    gl_Position = vec4(position.xyz, 1);
    normal_vertex = normal;
    position_vertex = position;
}