#version 420 core
layout (location = 0) in vec3 inputPos;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTexCoords;
layout (location = 3) in mat4 matModelInst;

out vec3 fragPos;
out vec2 fragTexCoords;
out vec3 fragNormal;


// uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
void main()
{
    mat4 translate1 = mat4(1.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  0.0, 3 * sin(time*2), 0.0, 1.0);
    vec3 pos = (translate1 * vec4(inputPos, 1.0)).xyz;
    fragPos = pos;
    fragTexCoords = inputTexCoords;
    mat3 normalMatrix = transpose(inverse(mat3(matModelInst)));
    fragNormal = normalMatrix * inputNormal;
    gl_Position = projection * view * matModelInst * vec4(pos, 1.0);
}  