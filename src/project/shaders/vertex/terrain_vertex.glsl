#version 330 core
layout (location = 0) in vec3 inputPos;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTexCoords;

uniform mat3 normalMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec2 fragTexCoords;
out vec3 fragNormal;
out float height;

void main()
{
    fragPos = inputPos;
    fragTexCoords = inputTexCoords;
    fragNormal = normalMatrix * inputNormal;
    height = inputPos.y;
    gl_Position = projection * view * model * vec4(inputPos, 1.0);
    // gl_Position =  view * model * vec4(inputPos, 1.0);
}