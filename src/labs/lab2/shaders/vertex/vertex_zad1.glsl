#version 330 core
layout (location = 0) in vec3 aPos;


void main()
{
    gl_PointSize = (gl_VertexID % 10) * 1.0f;
    gl_Position = vec4(aPos, 1.0);
}