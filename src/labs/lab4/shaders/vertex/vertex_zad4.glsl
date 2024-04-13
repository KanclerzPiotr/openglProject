#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

out vec2 texCoords;


void main()
{
    texCoords.x = aTexCoords.x + time;
    texCoords.y = aTexCoords.y;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}