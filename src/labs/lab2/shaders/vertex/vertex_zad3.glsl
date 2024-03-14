#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 translation;

void main()
{
    gl_Position = vec4(aPos.y, -aPos.x, aPos.z, 1.0) + vec4(translation.x, translation.y, 0.0, 0.0);
}