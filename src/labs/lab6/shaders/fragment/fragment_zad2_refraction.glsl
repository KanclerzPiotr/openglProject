#version 330 core
out vec4 FragColor;

in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 fragPos;

uniform vec3 cameraPos;
uniform samplerCube skybox;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{   
    vec4 color = texture(texture1, fragTexCoords);
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(fragPos - cameraPos);
    vec3 R = refract(I, normalize(fragNormal), ratio);
    vec4 reflection = vec4(texture(skybox, R).rgb, 1.0);
    FragColor = mix(reflection, color, 0.5);
}