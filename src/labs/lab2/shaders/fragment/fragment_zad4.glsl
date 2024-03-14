#version 330 core

uniform bool line;

out vec4 FragColor; 
in float dist;

void main() {

    vec3 color = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), dist/0.8);
    if (line)
        FragColor = vec4(1.0, 0, 0, 1.0);
    else
        FragColor = vec4(color, 1.0); 
}