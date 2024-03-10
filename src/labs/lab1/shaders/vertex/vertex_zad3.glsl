#version 330 core
layout (location = 0) in vec3 aPos;

uniform float pointSize;

void main()
{
    gl_PointSize = pointSize;
    gl_Position = vec4(aPos, 1.0);
}