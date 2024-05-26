#version 330 core
layout (location = 0) in vec3 inputPos;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTexCoords;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 fragTexCoords;

uniform mat3 normalMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragTexCoords = inputTexCoords;
    fragNormal = normalMatrix * inputNormal;
    fragPos = vec3(model * vec4(inputPos, 1.0));
    gl_Position = projection * view * vec4(fragPos, 1.0);
}  