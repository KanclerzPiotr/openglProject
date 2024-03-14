#version 330 core
layout (location = 0) in vec3 aPos;

out float dist;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    dist = length(aPos);
}