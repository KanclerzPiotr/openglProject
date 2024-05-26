#version 330 core
layout (location = 0) in vec3 inputPos;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTexCoords;
layout (location = 3) in mat4 matModelInst;

out vec2 fragTexCoords;

// uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragTexCoords = inputTexCoords;
    gl_Position = projection * view * matModelInst * vec4(inputPos, 1.0);
}  